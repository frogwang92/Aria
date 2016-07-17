#pragma once
#include "IMasterTimeHandler.h"
#include "../Data/Resolution.h"
#include <boost/thread.hpp>

class BacktestTimeHandler :
   public IMasterTimeHandler
{
public:
   BacktestTimeHandler(const boost::posix_time::ptime& start_time, Resolution res);
   ~BacktestTimeHandler();

public:
   virtual const boost::posix_time::ptime& get_current_time();
   void step();

private:
   boost::posix_time::ptime m_current_time;
   Resolution m_res;
   boost::mutex m_mutex;
};

