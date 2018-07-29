#pragma once

#include <thread>
#include <condition_variable>
#include <mutex>
#include "../tcpclient/TCPClient.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <map>
#include <atomic>
#include <iostream>
#include <unistd.h>

using namespace std;

class TCPServer
{
public:
    TCPServer(Parameters param, CoreFeaturePtr core);
    ~TCPServer();
    bool startServer();
    void stopServer();
    bool handle();
    void handleClient();
    void removeClient(TCPClientPtr client);
private:
    int m_sock;
    int m_port;
    string m_ipAddr;
    int m_numberClient;
    mutex m_mutex;
    std::atomic<bool> m_run;
    CoreFeaturePtr m_pCore;
    map<TCPClientPtr, thread> m_threads;
};

typedef shared_ptr<TCPServer> TCPServerPtr;
