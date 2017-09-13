#ifndef _GLOBAL_H_
#define _GOLBAL_H_

#ifdef WIN32
#pragma warning ( disable : 4251 ) // suppress warnings about DLLS
#endif

#include <memory>
#include <boost/date_time.hpp>

using std::shared_ptr;
using std::weak_ptr;
using std::unique_ptr;

using time_point = boost::posix_time::ptime;
using time_duration = boost::posix_time::time_duration;

using price_type = double;

#endif