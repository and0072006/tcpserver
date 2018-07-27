#pragma once

#include <functional>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <memory>


using namespace std;

struct Parameters
{
    int    time;
    int    port;
    string ipAddr;
    string logFile;
    bool switchLog;
    int    numberClient;
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
public:
    ~CoreFeature();

    void addCall(Function fun);
    void start();
    void stop();	
};

typedef shared_ptr<CoreFeature> CoreFeaturePtr;

