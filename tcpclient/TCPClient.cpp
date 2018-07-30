#include "TCPClient.h"

TCPClient::TCPClient(int sock, struct sockaddr_in addr, CoreFeaturePtr core, int timeWait)
{
    m_sock = sock;
    m_addr = addr;
    m_pCore = core;
    m_timeWait = timeWait;
    LOGI("Session has been established: id ") << m_sock
        << ", ip addres " << inet_ntoa(addr.sin_addr)
        << ", port " << ntohs(addr.sin_port) << "\n";
}

TCPClient::~TCPClient()
{
    LOGI("Session has been closed: id ") << m_sock << "\n";
    close(m_sock);
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
    recv(m_sock, (void*)&msg, sizeof(T_MSG), 0);
    msg.value = Worker::Factorial(msg.value);
    std::this_thread::sleep_for(std::chrono::seconds(m_timeWait));
    send(m_sock, (void*)&msg, sizeof(T_MSG), 0);
    m_pCore->addCall(m_fun);
    m_fun = NULL;
}
