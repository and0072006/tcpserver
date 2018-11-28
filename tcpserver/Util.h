#pragma once

#include <functional>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <memory>
#include <iostream>

using namespace std;

struct Parameters
{
    int    time;
    int    port;
    string ipAddr;
    string logFile;
    bool   allowLogging;
    int    maxClients;
    int    logLevel;
};

struct T_MSG
{
    int value;
    char msg[5];
};

typedef std::function<void()> Function;

class CoreFeature
{
private:
    vector<Function> m_functions;
    condition_variable m_cond;
    mutex m_mutex;
    atomic<bool> m_run;

    void handle();
    void info();
public:
    ~CoreFeature();

    void addCall(Function fun);
    void start();
    void stop();	
};

typedef shared_ptr<CoreFeature> CoreFeaturePtr;

class Worker
{
public:
    static int Factorial(int value);
};
