#include "../log/Logger.h"
#include "../conf/ConfigReader.h"
#include <iostream>
#include <stdio.h>

int main(int argc, char** argv)
{
    LoggerPtr pLog = std::make_shared<Logger>(new FileLogger("logfile"));
    pLog->Log("Test");
    ConfigReaderPtr pConf = std::make_shared<ConfigReader>(new TxtConfigReader());
    Parameters param;
    pConf->ReadConfig("config.txt",&param);

    std::cout << "Hello";
    return 0;
}
