#include "TCPServer.h"


void StartClient(TCPClientPtr client)
{
    client->start();
}

TCPServer::TCPServer(Parameters param, CoreFeaturePtr core)
{
    m_port = param.port;
    m_ipAddr = param.ipAddr;
    m_maxClients = param.maxClients;
    m_numberClients = 0;
    m_pCore = core;
    m_timeWait = param.time;
}

TCPServer::~TCPServer()
{
    stopServer();
}

bool TCPServer::startServer(){
    m_run = true;
    struct sockaddr_in addr;
    m_sock = socket(AF_INET, SOCK_STREAM, 0); 
    if (m_sock < 0)
    {
        LOGE("Couldn't open socket\n");
        return false;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(m_port);
    inet_aton(m_ipAddr.c_str(), &addr.sin_addr);

    if(bind(m_sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        LOGE("Couldn't bind socket\n");
        return false;
    }
    LOGD("TCPServer has been bind\n");

    listen(m_sock, m_maxClients);
    LOGD("TCPServer has been listen\n");

    return handle();
}

void TCPServer::stopServer() 
{
    LOGD("TCPServer stoping\n");
    m_run = false;
    unique_lock<mutex> lock(m_mutex);
    for(auto &it: m_threads)
    {
        it.first->stopClient();
        it.second.join();
    }
    m_threads.clear();
    shutdown(m_sock, 2);
    close(m_sock);
}

void TCPServer::removeClient(TCPClientPtr client) 
{
    unique_lock<mutex> lock(m_mutex);
    auto ithr = m_threads.find(client);
    (*ithr).second.join();
    if(ithr != m_threads.end())
    {
        m_threads.erase(ithr);
        LOGD("Client has been deleted\n");
    }
}

void TCPServer::handleClient() 
{
    int sockClient;
    struct sockaddr_in addr;
    int addrlen = sizeof(addr);
    if ((sockClient = accept(m_sock, (struct sockaddr*)&addr, (socklen_t*)&addrlen)) != 0) 
    {
        LOGI("Number of clients ") << ++m_numberClients << "\n";
        TCPClientPtr client = make_shared<TCPClient>(sockClient, addr, m_pCore, m_timeWait);
        Function func = bind(&TCPServer::removeClient, this, client);
        client->SetCall(func);
        {
            unique_lock<mutex> lock(m_mutex);
            m_threads[client] = thread(StartClient, client);
        }
    }
}

bool TCPServer::handle()
{
    while (m_run)
    {
        fd_set rfds;
        fd_set wfds;
        int res;
        struct timeval tv;
 
        FD_ZERO (&rfds);
        FD_SET (m_sock, &rfds);
        FD_ZERO (&wfds);
        FD_SET (m_sock, &wfds);

        tv.tv_sec = 5;
        tv.tv_usec = 0;

        res = select (m_sock + 1, &rfds, &wfds, NULL, &tv);
        if (res < 0) {
            LOGE("Error select\n");
            return false;
        }
        else if (!m_run) 
        {
            break;
        }
        else if (res == 0)
        {
            continue;
        }
 
        if (FD_ISSET(m_sock, &rfds) ||
            FD_ISSET(m_sock, &wfds)) 
        {
            handleClient();
        }
    }
    return true;
}
