
#include "DataInitializer.h"
#include "DataFeed_OHLCV.h"
#include "OHLCVReader_Py.h"
#include "Indicator_SMA.h"

using namespace boost::posix_time;

DataInitializer::DataInitializer(void) {
}

shared_ptr<IDataFeed> DataInitializer::init() {
  //
  ptime start(boost::gregorian::date(2005, 02, 01));
  ptime end(boost::gregorian::date(2016, 02, 01));
  auto p_feed = std::dynamic_pointer_cast<DataFeed>(std::make_shared<DataFeed_OHLCV>(start, end, Day));
  p_feed->add_reader(shared_ptr<OHLCVReader>(new OHLCVReader_Py(Symbol(600000))));
  p_feed->register_indicator(shared_ptr<Indicator>(new Indicator_SMA(Symbol(600000), "SMA_5", 5)));
  p_feed->register_indicator(shared_ptr<Indicator>(new Indicator_SMA(Symbol(600000), "SMA_9", 9)));
  p_feed->register_indicator(shared_ptr<Indicator>(new Indicator_SMA(Symbol(600000), "SMA_14", 14)));
  return p_feed;
}