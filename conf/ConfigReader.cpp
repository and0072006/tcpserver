#include "ConfigReader.h"


bool ConfigReader::ReadConfig(const string& file, Parameters* pParam)
{
    return m_pReader->ReadConfig(file, pParam);
}
