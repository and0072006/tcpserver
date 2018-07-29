
#include "Logger.h"


void Logger::Log(string str) 
{ 
    std::unique_lock<std::mutex> lok(m_mutex);
    m_pLImpl->log(str); 
}

void Logger::Log(long ll) 
{ 
    stringstream ss; 
    ss << ll;
    std::unique_lock<std::mutex> lok(m_mutex); 
    m_pLImpl->log(ss.str()); 
}
