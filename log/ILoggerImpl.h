#pragma once

#include <string.h>
#include <memory>

using namespace std;

class ILoggerImpl
{
public:
    virtual ~ILoggerImpl() = default;
    virtual void log(string str) const = 0;
};
