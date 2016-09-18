#include "stdafx.h"
#include "DataSlice.h"
#include "OHLCV.h"

using namespace boost::date_time;
using namespace boost::posix_time;

DataSlice::DataSlice(void)
   :m_res(Day),
   m_data(),
   m_starttime(not_a_date_time),
   m_endtime(not_a_date_time)
{
}

DataSlice::DataSlice(const boost::posix_time::ptime& starttime, Resolution res)
   :m_res(res),
   m_data(),
   m_starttime(starttime),
   m_endtime(m_starttime + boost::posix_time::time_duration(0, 0, res))
{
}

DataSlice::~DataSlice(void)
{
}

bool DataSlice::add_data(Symbol symbol, const boost::shared_ptr<OHLCV>& p_data)
{
   std::pair<std::map<Symbol, shared_ptr<OHLCV> >::iterator, bool> p = m_data.insert(std::make_pair(symbol, p_data));
   return p.second;
}

boost::shared_ptr<OHLCV> DataSlice::get_data(const Symbol& symbol)
{
   return m_data[symbol];
}

bool DataSlice::add_indicator(Symbol symbol, const std::string& indicator_name, double value)
{
   std::map<std::string, double>& indicator_map = m_indicators[symbol];

   std::pair<std::map<std::string, double>::iterator, bool> p 
      = indicator_map.insert(std::make_pair(indicator_name, value));
   return p.second;
}