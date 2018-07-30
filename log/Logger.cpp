
#include "Logger.h"


ILoggerImpl& Logger::Log(string head, string str) 
{ 
    m_pLImpl->log(head);
    m_pLImpl->log(str);
    return *m_pLImpl;
}

ILoggerImpl& Logger::Log(string head, long ll) 
{ 
    stringstream ss; 
    ss << head << ll;
    m_pLImpl->log(ss.str());
    return *m_pLImpl; 
}

void Logger::init(Parameters* param)
{
    m_logLevel = param->logLevel;
    m_allowLogging = param->allowLogging;
    m_pLImpl = new FileLogger(param->logFile);
}
