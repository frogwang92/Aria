#pragma once
#include<boost/date_time.hpp>
#include <boost/noncopyable.hpp>

class IMasterTimeHandler
   : boost::noncopyable
{
public:
   virtual const boost::posix_time::ptime get_current_time() = 0;
   virtual const boost::gregorian::date get_current_date() { return get_current_time().date(); }

public:
   virtual ~IMasterTimeHandler() {}
};