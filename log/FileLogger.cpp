#include "FileLogger.h"

FileLogger::FileLogger(string file):
    m_file(file)
{
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
    if (init())
    {
        m_out << str << endl;
        m_out.close();
    }
}
