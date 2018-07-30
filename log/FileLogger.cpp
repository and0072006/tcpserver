#include "FileLogger.h"

FileLogger::FileLogger(string file):
    m_file(file)
{
}

bool FileLogger::open()
{
    m_out.open(m_file, std::ios::app); 
    if (!m_out.is_open())
    {
        std::cerr << "Couldn't open log file" << std::endl;
        return false;
    }
    return true;
}

void FileLogger::close()
{
    m_out.close();
}


void FileLogger::log(string str)
{
    unique_lock<mutex> lock(m_mutex);
    if(open())
    {
        m_out << str;
        close();
    }
}

ILoggerImpl& FileLogger::operator<<(int x)
{
    {
        unique_lock<mutex> lock(m_mutex);
        if(open())
        {
            m_out << x;
            close();
        }
    }
    return *this;
}

ILoggerImpl& FileLogger::operator<<(string str)
{
    {
        unique_lock<mutex> lock(m_mutex);
        if(open())
        {
            m_out << str;
            close();
        }
    }
    return *this;
}

