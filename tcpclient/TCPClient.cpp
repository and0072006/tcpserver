#include "TCPClient.h"

TCPClient::TCPClient(int sock, struct sockaddr_in addr, CoreFeaturePtr core)
{
    m_sock = sock;
    m_addr = addr;
    m_pCore = core;
    LOGD("Client created\n");
    LOGI("Session has been established!");
}

TCPClient::~TCPClient()
{
    close(m_sock);
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
    LOGD(msg.value);
    msg.value = Worker::Factorial(msg.value);
    std::this_thread::sleep_for(std::chrono::seconds(10));
    send(m_sock, (void*)&msg, sizeof(T_MSG), 0);
    m_pCore->addCall(m_fun);
}
