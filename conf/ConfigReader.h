#pragma once

#include "../conf/IConfigReader.h"
#include "../conf/TxtConfigReader.h"
#include <memory>


class ConfigReader: public IConfigReader
{
private:
    IConfigReader* m_pReader;

public:
    ConfigReader(IConfigReader* pReader): m_pReader(pReader){};
    ~ConfigReader(){delete m_pReader;};

    bool ReadConfig(const string& file, Parameters* pParam);
};

typedef shared_ptr<ConfigReader> ConfigReaderPtr;
