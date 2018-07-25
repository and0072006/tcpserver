#pragma once

#include <string.h>
#include "../log/ILoggerImpl.h"
#include <iostream>


using namespace std;

class FileLogger: public ILoggerImpl
{
    string m_file;
public:
    FileLogger(string file): m_file(file){};
    virtual ~FileLogger(){};
    
    virtual void log(string str) const;

};
