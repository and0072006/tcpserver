#pragma once

#include "../conf/IConfigReader.h"
#include <iostream>


class TxtConfigReader: public IConfigReader
{
private:
    std::map<string,string> m_data;

public:

    virtual void ReadConfig(const string& file, Parameters* param);
};
