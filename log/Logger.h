#pragma once

#include <string.h>
#include "../log/ILoggerImpl.h"
#include "../log/FileLogger.h"
#include "../tcpserver/Util.h"
#include <memory>
#include <sstream>
#include <mutex>

enum LEVEL
{
    ERROR = 1,
    WARNING,
    INFO, 
    DEBUG
};

class Logger
{

public:
    ~Logger() { delete m_pLImpl;}

    static ILoggerImpl* m_pLImpl;
    static ILoggerImpl& Log(string head, string str);
    static ILoggerImpl& Log(string head, long ll);
    static void init(Parameters* param);
    static int m_logLevel;
    static int m_allowLogging;
};

#define LOG(level, ...) \
        if(level <= Logger::m_logLevel && Logger::m_allowLogging != 0) Logger::Log(__VA_ARGS__)

#define LOGE(...) LOG(LEVEL::ERROR, "ERROR ", ##__VA_ARGS__)
#define LOGI(...) LOG(LEVEL::INFO, "INFO ", ##__VA_ARGS__)
#define LOGD(...) LOG(LEVEL::DEBUG, "DEBUG ",##__VA_ARGS__)

typedef shared_ptr<Logger> LoggerPtr;
