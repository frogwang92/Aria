#pragma once
#ifdef DATA_EXPORTS
#define DATA_API __declspec(dllexport)
#else
#define DATA_API __declspec(dllimport)
#endif

#include "stdafx.h"
#include "ohlc.h"

class DATA_API OHLCV :
   public OHLC
{
public:
   OHLCV(void);
   OHLCV(int open, int close, int high, int low, int adj_close, int vol);
   OHLCV(int open, int close, int high, int low, int adj_close, const boost::posix_time::ptime& starttime, Resolution res, int vol);
   ~OHLCV(void);

public:
   int volume() const { return m_volume; }
   
private:
   int m_volume;
};

inline ostream & operator<<(ostream &stream, const OHLCV & right)
{
   stream << (OHLC)right << "," << right.volume();

   return stream;
}