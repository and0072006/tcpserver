#include "TCPClient.h"

TCPClient::TCPClient(int sock, struct sockaddr_in addr)
{
    m_sock = sock;
    m_addr = addr;
    //Log("Client created\n");
}

TCPClient::~TCPClient()
{
//    close(m_sock);
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
    recv(m_sock, buffer, sizeof(buffer), 0);
    //int result = Worker::Calculate(buffer);
    std::this_thread::sleep_for(std::chrono::seconds(10));
    send(m_sock, buffer, sizeof(buffer), 0);
    m_pCore->addCall(m_fun);
}
