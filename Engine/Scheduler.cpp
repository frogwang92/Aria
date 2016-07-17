#include "stdafx.h"
#include "Scheduler.h"
#include "TimeService.h"

using namespace boost;

Scheduler::Scheduler(const boost::posix_time::ptime& start_time, const boost::posix_time::time_duration& interval, Task task)
   : go_on(false),
   m_interval(interval),
   m_target_time(start_time),
   m_task(task)
{
   //m_pthread = shared_ptr<thread>(new thread(boost::bind(&Scheduler::ThreadLoop, this)));
}

Scheduler::~Scheduler() {
   go_on = false;
   //m_pthread->join();
}

// other thread wait on the signal for blocking
void Scheduler::run()
{
   go_on = true;
   ThreadLoop();
}

void Scheduler::ThreadLoop() {
   while (true)
   {
      if (go_on)
      {
         posix_time::ptime now = TimeService::now();
         if (m_target_time <= now)
         {
            std::cout << "target time is: " << m_target_time << ", now is: " << now;
            if (!m_task())
            {
               break;
            }
            m_target_time += m_interval;
         }
      }
   }
}
