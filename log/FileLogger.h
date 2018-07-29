#pragma once

#include <string.h>
#include "../log/ILoggerImpl.h"
#include <iostream>
#include <fstream>


using namespace std;

class FileLogger: public ILoggerImpl
{
    string m_file;
    ofstream m_out;
public:
    FileLogger(string file);
    virtual ~FileLogger(){ m_out.close();};
    
    virtual void log(string str);
    virtual ILoggerImpl& operator<<(int x);
    virtual ILoggerImpl& operator<<(string str);
    bool init();
};
