
#include "Logger.h"


void Logger::Log(string str) const
{
    pLImpl->log(str);
}
