#pragma once

#include <string.h>
#include "../log/ILoggerImpl.h"
#include "../log/FileLogger.h"
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
    static void Log(string str);
    static void Log(long ll);
    static int m_logLevel;
    static std::mutex m_mutex;
};

#define LOG(level, ...) \
        if(level <= Logger::m_logLevel) Logger::Log(__VA_ARGS__)

#define LOGE(...) LOG(LEVEL::ERROR, ##__VA_ARGS__)
#define LOGI(...) LOG(LEVEL::INFO, ##__VA_ARGS__)
#define LOGD(...) LOG(LEVEL::DEBUG, ##__VA_ARGS__)

typedef shared_ptr<Logger> LoggerPtr;
