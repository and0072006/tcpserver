#include "FileLogger.h"

FileLogger::FileLogger(string file):
    m_file(file)
{
    init();
}

bool FileLogger::init()
{
    m_out.open(m_file, std::ios::app); 
    if (!m_out.is_open())
    {
        std::cerr << "Couldn't open log file" << std::endl;
        return false;
    }
    return true;
}

void FileLogger::log(string str)
{
    m_out << str;
}

ILoggerImpl& FileLogger::operator<<(int x)
{
    m_out << x;
    return *this;
}

ILoggerImpl& FileLogger::operator<<(string str)
{
    m_out << str;
    return *this;
}

