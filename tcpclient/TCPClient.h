#pragma once

#include <memory>
#include <vector>
#include <condition_variable>
#include "../tcpserver/Util.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <thread>


using namespace std;

class TCPClient
{
public:
    TCPClient(int sock, struct sockaddr_in addr);
    ~TCPClient();
    void handle();
    void SetCall(Function fun);
    void start();
private:
    int m_sock;
    struct sockaddr_in m_addr;
    char buffer[1024];
    CoreFeaturePtr m_pCore;
    Function m_fun;
};

typedef shared_ptr<TCPClient> TCPClientPtr;
