#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#include "global.h"
#include <map>
#include <functional>
#include <boost/date_time.hpp>
#include <boost/thread.hpp>
#include <boost/noncopyable.hpp>

typedef std::function<bool()> Task;

//Single threaded scheduler
class Scheduler 
   : boost::noncopyable
{

public:
   Scheduler(const boost::posix_time::ptime& start_time, const boost::posix_time::time_duration& interval, Task task);
   ~Scheduler();

   void run();

private:
   void ThreadLoop();

private:
   boost::mutex m_mutex;
   shared_ptr<boost::thread> m_pthread;
   bool go_on;
   boost::posix_time::time_duration m_interval;
   boost::posix_time::ptime m_target_time;
   Task m_task;
};

#endif