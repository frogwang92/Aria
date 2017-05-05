#ifndef _RESOLUTION_H_
#define _RESOLUTION_H_

#include <boost/date_time.hpp>
enum Resolution
{
   Second = 1,
   FiveSeconds = 5,
   TenSeconds = 10,
   Minute = 60,
   FiveMinutes = 300,
   Hour = 3600,
   TwoHours = 7200,
   Day = 86400
};

inline boost::posix_time::time_duration duration(Resolution res)
{
   return boost::posix_time::time_duration(0, 0, res);
}

#endif