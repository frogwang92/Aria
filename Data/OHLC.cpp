#include "StdAfx.h"
#include "OHLC.h"

using namespace boost::posix_time;

OHLC::OHLC(void)
   :m_open(0),
   m_close(0),
   m_high(0),
   m_low(0),
   m_adjclose(0),
   m_starttime(not_a_date_time),
   m_endtime(not_a_date_time)
{
}

OHLC::OHLC(int open, int close, int high, int low, int adj_close)
   :m_open(open),
   m_close(close),
   m_high(high),
   m_low(low),
   m_adjclose(adj_close),
   m_starttime(not_a_date_time),
   m_endtime(not_a_date_time)
{}

OHLC::OHLC(int open, int close, int high, int low, int adj_close, const ptime& starttime, Resolution res)
   :m_open(open),
   m_close(close),
   m_high(high),
   m_low(low),
   m_adjclose(adj_close),
   m_starttime(starttime)
{
   m_endtime = m_starttime + time_duration(0, 0, res);
}

OHLC::~OHLC(void)
{
}
