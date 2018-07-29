#pragma once

#include <string.h>
#include <memory>
#include <fstream>

using namespace std;

class ILoggerImpl
{
public:
    virtual ~ILoggerImpl() = default;
    virtual void log(string str) = 0;
    virtual ILoggerImpl& operator<<(int x) = 0;
    virtual ILoggerImpl& operator<<(string str) = 0;
};
