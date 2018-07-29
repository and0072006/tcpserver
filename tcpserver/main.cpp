#include "../log/Logger.h"
#include "../conf/ConfigReader.h"
#include "../tcpserver/Util.h"
#include "../tcpserver/TCPServer.h"
#include <iostream>
#include <stdio.h>
#include <condition_variable>
#include <mutex>
#include <future>


void StartCoreFeature(CoreFeaturePtr core, std::condition_variable* cond, std::mutex* mut)
{
    {
        unique_lock<mutex> lock(*mut);
        cond->notify_all();
    }
    core->start();
}

void StartServer(TCPServerPtr server, std::condition_variable* cond, std::mutex* mut)
{
    {
        unique_lock<mutex> lock(*mut);
        cond->notify_all();
    }
    server->startServer();
}

int Logger::m_logLevel = 1;
ILoggerImpl* Logger::m_pLImpl = NULL;
std::mutex Logger::m_mutex;

int main(int argc, char** argv)
{
    LoggerPtr pLog = std::make_shared<Logger>();
    ConfigReaderPtr pConf = std::make_shared<ConfigReader>(new TxtConfigReader());
    Parameters param;
    if (!pConf->ReadConfig("/home/anvecher/server/conf/config.txt",&param))
    {
        LOGE("Couldn't read config file\n");
        return 0;
    }
    Logger::m_logLevel = param.logLevel;
    Logger::m_pLImpl = new FileLogger(param.logFile);

    std::condition_variable cond;
    std::mutex lmutex;

    CoreFeaturePtr pCoreFeature = make_shared<CoreFeature>();
    unique_lock<std::mutex> lock(lmutex);    
    auto coreFeatureThread = async(launch::async,
                                   StartCoreFeature,
                                   pCoreFeature,
                                   &cond,
                                   &lmutex);
    cond.wait(lock); 
    LOGD("Core Feature has been started\n");
    TCPServerPtr pServer = make_shared<TCPServer>(param, pCoreFeature);
    auto TCPSreverThread = async(launch::async,
                                 StartServer,
                                 pServer,
                                 &cond,
                                 &lmutex);
    cond.wait(lock);
    LOGD("TCPServer has been started\n");

    char str[10];
    while(cin.getline(str, 10))
    {
        if(strcmp(str, "stop") == 0)
            break;
    }

    pServer->stopServer();
    TCPSreverThread.get();
    LOGD("TCPServer has been stoped\n");
    pCoreFeature->stop();
    coreFeatureThread.get();
    LOGD("Core Feature has been stoped\n");
    return 0;
}
