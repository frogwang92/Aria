#include "StdAfx.h"
#include "DataFeed.h"
#include <boost/thread.hpp>
#include <boost/foreach.hpp>
#include "Indicator.h"
#include "OHLCVReader.h"

using namespace boost;
using namespace boost::posix_time;

DataFeed::DataFeed(void)
   : m_active(false),
   m_start_time(not_a_date_time),
   m_end_time(not_a_date_time),
   m_curr_time(not_a_date_time),
   m_res(Day)
{
}

DataFeed::DataFeed(const boost::posix_time::ptime& start_time, const boost::posix_time::ptime& endtime, Resolution res)
   :m_active(false),
   m_start_time(start_time),
   m_end_time(endtime),
   m_curr_time(not_a_date_time),
   m_res(res)
{
}

DataFeed::~DataFeed(void)
{
}

bool DataFeed::operator>> (shared_ptr<DataSlice>& p_data)
{
   if( m_curr_time != not_a_date_time && m_curr_time >= m_end_time )
      return false;
   else
   {
      p_data = get();
      m_curr_time = p_data->get_start_time();
   }
   return true;
}

shared_ptr<DataSlice> DataFeed::get()
{
   if( !is_active() )
   {
      BOOST_FOREACH(shared_ptr<OHLCVReader> reader, m_readers)
      {
         reader->read();
      }
      m_active = true;
      std::cout << "data feed start pumping, end time is " << get_endtime() << std::endl;
      boost::thread pumpthread(boost::bind(&DataFeed::pumping_data, this));
   }
   return m_queue.pop();
}

void DataFeed::register_indicator(const shared_ptr<Indicator>& indicator)
{
   m_indicators.push_back(indicator);
}

void DataFeed::push_slice(const shared_ptr<DataSlice>& p_slice)
{
   m_queue.push(p_slice);
   BOOST_FOREACH(boost::shared_ptr<Indicator> indicator, m_indicators)
   {
      indicator->calculate(p_slice);
   }
}
