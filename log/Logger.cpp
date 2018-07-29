
#include "Logger.h"


ILoggerImpl& Logger::Log(string head, string str) 
{ 
    std::unique_lock<std::mutex> lok(m_mutex);
    m_pLImpl->log(head);
    m_pLImpl->log(str);
    return *m_pLImpl;
}

ILoggerImpl& Logger::Log(string head, long ll) 
{ 
    stringstream ss; 
    ss << head << ll;
    std::unique_lock<std::mutex> lok(m_mutex); 
    m_pLImpl->log(ss.str());
    return *m_pLImpl; 
}
