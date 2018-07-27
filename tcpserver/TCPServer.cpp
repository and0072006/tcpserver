#include "TCPServer.h"


void StartClient(TCPClientPtr client)
{
    client->start();
}

TCPServer::TCPServer(Parameters param)
{
    m_port = param.port;
    m_ipAddr = param.ipAddr;
    m_numberClient = param.numberClient;
}

TCPServer::~TCPServer()
{
    stopServer();
}

void TCPServer::startServer(){
    struct sockaddr_in addr;
    m_sock = socket(AF_INET, SOCK_STREAM, 0); 
    if (m_sock < 0)
    {
//        Log("Couldn't open socket.");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(m_port);
    addr.sin_addr.s_addr=inet_addr(m_ipAddr.c_str());

    if(bind(m_sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
//        Log("Couldn't bind socket.");
        exit(2);
    }

    listen(m_sock, m_numberClient);

    handle();
}

void TCPServer::stopServer() 
{
    unique_lock<mutex> lock(m_mutex);
    for(auto &it: m_threads)
        it.second.join();
    m_threads.clear();
    //close(m_sock);
//    Log("Server was stoped.");
}

void TCPServer::removeClient(TCPClientPtr client) 
{
    unique_lock<mutex> lock(m_mutex);
    auto ithr = m_threads.find(client);
    if(ithr != m_threads.end())
        m_threads.erase(ithr);
}

void TCPServer::handle() 
{
    while (true)
    {
        int sockClient;
        struct sockaddr_in addr;
        int addrlen = sizeof(addr);
        if ((sockClient = accept(m_sock, (struct sockaddr*)&addr, (socklen_t*)&addrlen)) != 0) 
        {
            printf("send\n");
//            printf("sended Client connected from 0  %u.%u.%u.%u:%u\n",
//                  (unsigned char)addr.sin_addr.S_un.S_un_b.s_b1,
//                  (unsigned char)addr.sin_addr.S_un.S_un_b.s_b2,
//                  (unsigned char)addr.sin_addr.S_un.S_un_b.s_b3,
//                  (unsigned char)addr.sin_addr.S_un.S_un_b.s_b4,
//                  ntohs(addr_c.sin_port));
            TCPClientPtr client = make_shared<TCPClient>(sockClient, addr);
            Function func = bind(&TCPServer::removeClient, this, client);
            client->SetCall(func);
            {
                unique_lock<mutex> lock(m_mutex);
                m_threads[client] = thread(StartClient, client);
            }
        }
    }
}
