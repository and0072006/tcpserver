#pragma once

#include "../conf/IConfigReader.h"
#include <iostream>


class TxtConfigReader: public IConfigReader
{
public:

    virtual void ReadConfig(const string& file, Parameters* param);
};
