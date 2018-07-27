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


int main(int argc, char** argv)
{
    LoggerPtr pLog = std::make_shared<Logger>(new FileLogger("logfile"));
    pLog->Log("Test");
    ConfigReaderPtr pConf = std::make_shared<ConfigReader>(new TxtConfigReader());
    Parameters param;
    pConf->ReadConfig("config.txt",&param);

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

    TCPServerPtr server = make_shared<TCPServer>(param);
    server->startServer();

    std::cout << "Hello";
    return 0;
}
