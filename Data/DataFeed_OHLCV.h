#pragma once
#ifndef _DATAFEED_OHLCV_H_
#define _DATAFEED_OHLCV_H_

#include "DataFeed.h"
#include <boost/noncopyable.hpp>

class DataFeed_OHLCV :
   public DataFeed
{
public:
   DataFeed_OHLCV(const boost::posix_time::ptime& start_time, const boost::posix_time::ptime& end_time, Resolution res);
   virtual ~DataFeed_OHLCV(void);

protected:
   void pumping_data();
};

#endif