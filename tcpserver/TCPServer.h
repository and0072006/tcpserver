#pragma once

#include <thread>
#include <condition_variable>
#include <mutex>
#include "../tcpclient/TCPClient.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <map>

using namespace std;

class TCPServer
{
public:
    TCPServer(Parameters param);
    ~TCPServer();
    void startServer();
    void stopServer();
    void handle();
    void removeClient(TCPClientPtr client);
private:
    int m_sock;
    int m_port;
    string m_ipAddr;
    int m_numberClient;
    mutex m_mutex;
    map<TCPClientPtr, thread> m_threads;
};

typedef shared_ptr<TCPServer> TCPServerPtr;
