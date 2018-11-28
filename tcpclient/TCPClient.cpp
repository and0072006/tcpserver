#include "TCPClient.h"

TCPClient::TCPClient(int sock, struct sockaddr_in addr, CoreFeaturePtr core, int timeWait)
{
    m_sock = sock;
    m_addr = addr;
    m_pCore = core;
    m_timeWait = timeWait;
    m_run = true;
    LOGI("Session has been established: id ") << m_sock
        << ", ip addres " << inet_ntoa(addr.sin_addr)
        << ", port " << ntohs(addr.sin_port) << "\n";
}

TCPClient::~TCPClient()
{
    LOGI("Session has been closed: id ") << m_sock << "\n";
    stopClient();
}

void TCPClient::stopClient()
{
    if (m_run)
    {
        m_run = false;
        shutdown(m_sock, 2);
        close(m_sock);
    }
}

int TCPClient::GetSocket() const
{
    return m_sock;
}

void TCPClient::SetCall(Function fun)
{
    m_fun = fun;
}

void TCPClient::start()
{
    handle();
}

void TCPClient::handle()
{
    T_MSG msg;
    int res;
    while(m_run)
    {
        res = recv(m_sock, (void*)&msg, sizeof(T_MSG), 0);
        if (!m_run || res == -1 || res <=0 || std::string(msg.msg) == "bye")
        {
            m_pCore->addCall(m_fun);
            m_fun = NULL;
            break;
        }

        msg.value = Worker::Factorial(msg.value);
        //std::this_thread::sleep_for(std::chrono::seconds(m_timeWait));
        res = send(m_sock, (void*)&msg, sizeof(T_MSG), 0);
    }
}
