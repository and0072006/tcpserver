#include "Util.h"
#include "../log/Logger.h"

CoreFeature::~CoreFeature()
{
    unique_lock<mutex> lk(m_mutex);
    m_functions.clear();
}


void CoreFeature::start()
{
    m_run = true;
    handle();
}

void CoreFeature::stop()
{
    m_run = false;
    Function fun = bind(&CoreFeature::info, this);
    addCall(fun);
    m_cond.notify_all();
}

void CoreFeature::info()
{
    LOGD("Core Feature stoping\n");
}

void CoreFeature::handle()
{
    while(m_run)
    {
        Function fun;
        {
            unique_lock<mutex> lk(m_mutex);
            m_cond.wait(lk, [this]{ return !m_functions.empty();});
            auto it = m_functions.begin();
            fun = *it;
            if(it != m_functions.end())
            m_functions.erase(it);
        }
        fun();
    }
}

void CoreFeature::addCall(Function fun)
{
    unique_lock<mutex> lk(m_mutex);
    m_functions.push_back(fun);
    m_cond.notify_all();
}



int Worker::Factorial(int value)
{
  int res = 1, i;
  for (i = 1; i <= value; i++) {
        res = res * i;
  }
  return res;
}
