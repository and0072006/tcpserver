#pragma once

#include "../conf/IConfigReader.h"
#include <iostream>
#include <map>
#include <fstream>

class TxtConfigReader: public IConfigReader
{
private:
    std::map<string,string> m_data;

    bool init(const string& file);
public:

    virtual bool ReadConfig(const string& file, Parameters* param);
};
