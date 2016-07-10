#include "StdAfx.h"
#include "OHLCV.h"

OHLCV::OHLCV(void)
{
}

OHLCV::OHLCV(int open, int close, int high, int low, int adj_close, int vol)
   :OHLC(open, close, high, low, adj_close),
   m_volume(vol)
{}

OHLCV::OHLCV(int open, int close, int high, int low, int adj_close, const boost::posix_time::ptime& starttime, Resolution res, int vol)
   :OHLC(open, close, high, low, adj_close, starttime, res),
   m_volume(vol)
{}

OHLCV::~OHLCV(void)
{
}
