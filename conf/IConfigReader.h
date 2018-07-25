#pragma once

#include <string>

using namespace std;

struct Parameters
{
    string logFile;
    int time;
    bool switchLog;
};


class IConfigReader
{
public:
    virtual ~IConfigReader() = default;

    virtual void ReadConfig(const string& file, Parameters* pParam) = 0;
};
