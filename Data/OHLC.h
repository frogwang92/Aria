#pragma once
#ifdef DATA_EXPORTS
#define DATA_API __declspec(dllexport)
#else
#define DATA_API __declspec(dllimport)
#endif

#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "global.h"
#include "Resolution.h"

class DATA_API OHLC
{
public:
   OHLC(void);
   //in cent
   OHLC(int open, int close, int high, int low, int adj_close);
   OHLC(int open, int close, int high, int low, int adj_close, const boost::posix_time::ptime& starttime, Resolution res);
   virtual ~OHLC(void);

public:
   virtual int open() const { return m_open; }
   virtual int close() const { return m_close; }
   virtual int high() const { return m_high; }
   virtual int low() const { return m_low; }
   virtual int adj_close() const { return m_adjclose; }
   const boost::posix_time::ptime& start_time() const { return m_starttime; }
   const boost::posix_time::ptime& end_time() const { return m_endtime; }

private:
   int m_open;
   int m_close;
   int m_high;
   int m_low;
   int m_adjclose;
   boost::posix_time::ptime m_starttime;
   boost::posix_time::ptime m_endtime;
};

using std::ostream;

inline ostream & operator<<(ostream &stream, const OHLC & right)
{
   if (right.end_time() - right.start_time() == boost::posix_time::time_duration(0, 0, Day))
   {
      stream << to_iso_extended_string(right.start_time().date()) << ","
         << right.open() << ","
         << right.high() << ","
         << right.low() << ","
         << right.close() << ","
         << right.adj_close();
   }
   else
   {
      stream << right.start_time() << ","
         << right.end_time() << ","
         << right.open() << ","
         << right.high() << ","
         << right.low() << ","
         << right.close() << ","
         << right.adj_close();
   }
   
   return stream;
}