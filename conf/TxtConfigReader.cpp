#include "TxtConfigReader.h"

bool TxtConfigReader::init(const string& file)
{
    int length = 1024;
    char buff[length];
    ifstream fin(file);
    if (!fin.is_open())
    {
        return false;
    }
    while(fin.getline(buff, length))
    {
        string str = buff;
        std::string::size_type offer = str.find(" ", 0);
        if(offer != string::npos)
        {
            m_data[str.substr(0, offer)] = str.substr(offer + 1);
        }
    }
    fin.close();
    return true;
}

bool TxtConfigReader::ReadConfig(const string& file, Parameters* param)
{
    if(!init(file))
    {
        return false;
    }

    if (m_data.find("Port") == m_data.end())
    {
        return false;
    }
    param->port = atoi(m_data["Port"].c_str()); 

    if (m_data.find("IPAddr") == m_data.end())
    {
        return false;
    }
    param->ipAddr = m_data["IPAddr"];

    if (m_data.find("MaxClients") == m_data.end())
    {
        return false;
    }
    param->maxClients = atoi(m_data["MaxClients"].c_str());

    if (m_data.find("TimeWait") == m_data.end())
    {
        return false;
    }
    param->time = atoi(m_data["TimeWait"].c_str());

    if (m_data.find("LogFile") == m_data.end())
    {
        return false;
    }
    param->logFile = m_data["LogFile"];

    if (m_data.find("AllowLogging") == m_data.end())
    {
        return false;
    }
    param->allowLogging = atoi(m_data["AllowLogging"].c_str());
    if (m_data.find("LogLevel") == m_data.end())
    {
        return false;
    }
    param->logLevel = atoi(m_data["LogLevel"].c_str());
    return true;
}


