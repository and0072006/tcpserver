#include "TxtConfigReader.h"

bool TxtConfigReader::init(const string& file)
{
    int length = 1024;
    char buff[lrngth];
    ifstream fin("cppstudio.txt");
    if (!fin.is_open())a
    {
        cout << "Файл не может быть открыт!\n";
        returt false;
    }
    while(fin.getline(buff, length))
    {
        string str = buff;
        int offer = str.find(" ", 0);
        if(offer != string::npos)
        {
            m_data[str.substr(0, offer)] = str.substr(offer + 1);
        }
    }
    fin.close();
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
    param.port = m_data["Port"]; 

    if (m_data.find("IPAddr") == m_data.end())
    {
        return false;
    }
    param.ipAddr = m_data["IPAddr"];

    if (im_data.find("NumberClients") == m_data.end())
    {
        return false;
    }
    param.numberClient = m_data["NumberClients"];

    if (m_data.find("TimeWait") == m_data.end())
    {
        return false;
    }
    param.time = m_data["TimeWait"];

    if (m_data.find("LogFile") == m_data.end())
    {
        return false;
    }
    param.logFile = m_data["LogFile"];

    if (m_data.find("AllowLogging") == m_data.end())
    {
        return false;
    }
    param.switchLog = m_data["AllowLogging"];

    return true
}


