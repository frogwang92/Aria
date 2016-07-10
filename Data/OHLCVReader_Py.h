#pragma once

#include <boost/python.hpp>
#include <boost/thread.hpp>
#include "Symbol.h"
#include "ohlcvreader.h"

class DATA_API OHLCVReader_Py :
   public OHLCVReader
{
public:
   explicit OHLCVReader_Py(const Symbol& symbol);
   ~OHLCVReader_Py(void);

public:
   virtual void read();
   const Symbol& get_symbol() { return m_symbol; }

public:
   // callback func used by python script
   //void push_data(boost::shared_ptr<OHLCV> p_data);
   void push_data(int open, int close, int high, int low, int adj_close, const boost::posix_time::ptime& starttime, Resolution res, int vol);

private:
   // for start the python script
   void read_impl();
   Symbol m_symbol;
   shared_ptr<boost::thread> m_pthread;
};

