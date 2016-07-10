#pragma once
#include "OHLCV.h"
#include "../Common/BlockingQueue.h"
#include <boost/noncopyable.hpp>

struct Symbol;

class OHLCVReader
   : boost::noncopyable
{
public:
   OHLCVReader(void);
   virtual ~OHLCVReader(void);

public:
   virtual void read() = 0;
   virtual const Symbol& get_symbol() = 0;
   boost::shared_ptr<OHLCV> get() { return m_queue.pop(); }

protected:
   BlockingQueue<boost::shared_ptr<OHLCV> > m_queue;
};

