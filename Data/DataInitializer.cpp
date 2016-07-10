#include "StdAfx.h"
#include "DataInitializer.h"
#include "DataFeed_OHLCV.h"
#include "OHLCVReader_Py.h"
#include "Symbol.h"
#include "Resolution.h"
#include <boost/date_time.hpp>
#include <iostream>
#include "Indicator_SMA.h"

using namespace boost;
using namespace boost::posix_time;

DataInitializer::DataInitializer(void)
{
}

boost::shared_ptr<IDataFeed> DataInitializer::init()
{
   //
   ptime start(boost::gregorian::date(2005, 02, 01));
   ptime end(boost::gregorian::date(2016, 02, 01));
   shared_ptr<DataFeed> p_feed = shared_ptr<DataFeed>(new DataFeed_OHLCV(start, end, Day));
   p_feed->add_reader(boost::shared_ptr<OHLCVReader>(new OHLCVReader_Py(Symbol(600000))));
   p_feed->register_indicator(boost::shared_ptr<Indicator>(new Indicator_SMA(Symbol(600000), "SMA_5", 5)));
   p_feed->register_indicator(boost::shared_ptr<Indicator>(new Indicator_SMA(Symbol(600000), "SMA_9", 9)));
   p_feed->register_indicator(boost::shared_ptr<Indicator>(new Indicator_SMA(Symbol(600000), "SMA_14", 14)));
   return p_feed;
}