#ifndef _OHLCVREADER_H_
#define _OHLCVREADER_H_

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

    shared_ptr<OHLCV> get() { return m_queue.pop(); }

protected:
    BlockingQueue<shared_ptr<OHLCV> > m_queue;
};

#endif