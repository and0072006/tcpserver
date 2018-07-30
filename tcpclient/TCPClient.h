#pragma once

#include <memory>
#include <vector>
#include <condition_variable>
#include "../tcpserver/Util.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <thread>
#include <unistd.h>
#include "../log/Logger.h"

using namespace std;

class TCPClient
{
public:
    TCPClient(int sock, struct sockaddr_in addr, CoreFeaturePtr core, int timeWait);
    ~TCPClient();
    void handle();
    void SetCall(Function fun);
    void start();
    int GetSocket() const;
private:
    int m_sock;
    struct sockaddr_in m_addr;
    CoreFeaturePtr m_pCore;
    Function m_fun;
    int m_timeWait;
};

typedef shared_ptr<TCPClient> TCPClientPtr;
