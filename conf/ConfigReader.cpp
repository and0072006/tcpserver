#include "ConfigReader.h"


void ConfigReader::ReadConfig(const string& file, Parameters* pParam)
{
    m_pReader->ReadConfig(file, pParam);
}
