
#include <boost/date_time.hpp>

#include "logger.h"
#include "DataFeed_OHLCV.h"
#include "OHLCV.h"
#include "DataSlice.h"
#include "OHLCVReader.h"

using namespace boost::posix_time;

DataFeed_OHLCV::DataFeed_OHLCV(const boost::posix_time::ptime& start_time, const boost::posix_time::ptime& end_time, Resolution res)
   :DataFeed(start_time, end_time, res)
{
}

DataFeed_OHLCV::~DataFeed_OHLCV(void)
{
}

void DataFeed_OHLCV::pumping_data()
{
   auto cur_time = get_starttime();
   time_duration interval(0, 0, get_res());
   while(cur_time <= get_endtime())
   {
      auto iter = m_readers.begin();
      //first reader as time-axis
      auto p_first_data = (*iter)->get();
      if( p_first_data->start_time() >= cur_time )
      {
         while( p_first_data->start_time() > cur_time )
         {
            cur_time = cur_time + interval;
         }
          auto p_slice = std::make_shared<DataSlice>(cur_time, get_res());
         p_slice->add_data( (*iter)->get_symbol(), p_first_data);
         ++iter;
         // get from other readers
         while( iter != m_readers.end())
         {
            auto p_data = (*iter)->get();
            if( p_data->start_time() == cur_time )
            {
               p_slice->add_data( (*iter)->get_symbol(), p_data);
            }
            ++iter;
         }
         
         push_slice(p_slice);
      }
      else  // data is useless, pop and discard
      {
         ++iter;
         while( iter != m_readers.end())
         {
            (*iter)->get();
            ++iter;
         }
      }
      cur_time = cur_time + interval;
   }
}