#pragma once
#include "global.h"
#include <boost/noncopyable.hpp>
#include <boost/date_time.hpp>
#include "IMasterTimeHandler.h"
#include "Singleton.h"

class TimeService
   : boost::noncopyable
{
   friend class Singleton<TimeService>;

public:
   static const boost::posix_time::ptime now()
   {
      return get_current_time();
   }

   static const boost::posix_time::ptime get_current_time()
   {
      assert(Singleton<TimeService>::instance().m_handler != 0);
      return Singleton<TimeService>::instance().m_handler->get_current_time();
   }

   static const boost::gregorian::date get_current_date()
   {
      assert(Singleton<TimeService>::instance().m_handler != 0);
      return Singleton<TimeService>::instance().m_handler->get_current_date();
   }

public:
   void register_handler(const shared_ptr<IMasterTimeHandler>& p_handler)
   {
      m_handler = p_handler;
   }

private:
   TimeService(void)
      :m_handler(0)
   {}

private:
   shared_ptr<IMasterTimeHandler> m_handler;
};
