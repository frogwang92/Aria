#pragma once
#ifndef _DATAFEED_H_
#define _DATAFEED_H_

#include "BlockingQueue.h"
#include "global.h"

#include <boost/noncopyable.hpp>
#include <boost/date_time.hpp>
#include <boost/thread.hpp>
#include "Resolution.h"
#include <vector>
#include "IDataFeed.h"

class Indicator;
class OHLCVReader;
class DataSlice;

class DataFeed
   : public boost::noncopyable,
   public IDataFeed
{
public:
   DataFeed(void);
   DataFeed(const boost::posix_time::ptime& start_time, const boost::posix_time::ptime& endtime, Resolution res);
   virtual ~DataFeed(void);
   
   virtual bool is_active() const { return m_active; }
   void add_reader(const shared_ptr<OHLCVReader>& reader) { m_readers.push_back(reader); }

public:
   const boost::posix_time::ptime& get_starttime() { return m_start_time; }
   const boost::posix_time::ptime& get_endtime() { return m_end_time; }
   Resolution get_res() { return m_res; }
   void register_indicator(const shared_ptr<Indicator>& indicator);
   
public:
   bool operator>> (shared_ptr<DataSlice>& p_data);
   shared_ptr<DataSlice> head();

protected:
   virtual shared_ptr<DataSlice> get();
   virtual void pumping_data() = 0;
   void push_slice(const boost::shared_ptr<DataSlice>& p_slice);
   
protected:
   bool m_active;
   std::vector<shared_ptr<OHLCVReader> > m_readers;
   
private:
   void run();

private:
   boost::posix_time::ptime m_start_time;
   boost::posix_time::ptime m_end_time;
   boost::posix_time::ptime m_curr_time;
   Resolution m_res;
   std::vector<shared_ptr<Indicator> > m_indicators;
   BlockingQueue<shared_ptr<DataSlice> > m_queue;
   shared_ptr<boost::thread> m_pthread;
};

#endif