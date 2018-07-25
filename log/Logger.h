#pragma once

#include <string.h>
#include "../log/ILoggerImpl.h"
#include "../log/FileLogger.h"
#include <memory>


class Logger
{
private:
    ILoggerImpl* pLImpl;

public:
    Logger(ILoggerImpl* pLogImpl): pLImpl(pLogImpl) {}
    ~Logger() { delete pLImpl;}

    void Log(string str) const;
};

typedef shared_ptr<Logger> LoggerPtr;
