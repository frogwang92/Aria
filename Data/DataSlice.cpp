
#include "DataSlice.h"
#include "OHLCV.h"

using namespace boost::date_time;
using namespace boost::posix_time;

DataSlice::DataSlice(void)
    : m_res(Day),
      m_data(),
      m_starttime(not_a_date_time),
      m_endtime(not_a_date_time) {
}

DataSlice::DataSlice(const boost::posix_time::ptime &starttime, Resolution res)
    : m_res(res),
      m_data(),
      m_starttime(starttime),
      m_endtime(m_starttime + boost::posix_time::time_duration(0, 0, res)) {
}

DataSlice::~DataSlice(void) {
}

bool DataSlice::add_data(Symbol symbol, const shared_ptr<OHLCV> &p_data) {
  auto p = m_data.insert(std::make_pair(symbol, p_data));
  return p.second;
}

shared_ptr<OHLCV> DataSlice::get_data(const Symbol &symbol) {
  return m_data[symbol];
}

bool DataSlice::add_indicator(Symbol symbol, const std::string &indicator_name, double value) {
  auto &indicator_map = m_indicators[symbol];
  auto p = indicator_map.insert(std::make_pair(indicator_name, value));
  return p.second;
}