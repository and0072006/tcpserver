#pragma once

#include <string.h>
#include "../log/ILoggerImpl.h"
#include <iostream>
#include <fstream>
#include <mutex>

using namespace std;

class FileLogger: public ILoggerImpl
{
    string m_file;
    ofstream m_out;
    mutex m_mutex;
    
public:
    FileLogger(string file);
    virtual ~FileLogger(){ m_out.close();};
    
    virtual void log(string str);
    virtual ILoggerImpl& operator<<(int x);
    virtual ILoggerImpl& operator<<(string str);
    bool open();
    void close();
};
