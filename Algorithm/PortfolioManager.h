#ifndef _PORTFOLIO_MANAGER_H_
#define _PORTFOLIO_MANAGER_H_

#include "global.h"
#include "BlockingQueue.h"
#include "../Data/Symbol.h"
#include <boost/thread/mutex.hpp>
#include <boost/date_time.hpp>
#include "mode.h"

class Portfolio;
class Brokerage;
class TradeJobNode;
class DataSlice;

class PortfolioManager
{
public:
   PortfolioManager();
   explicit PortfolioManager(Mode mode);
   ~PortfolioManager(void);

public:
   void buy(const boost::posix_time::ptime& time_point, Symbol symbol, double price, double percentage);
   void sell(const boost::posix_time::ptime& time_point, Symbol symbol, double price, double percentage);
   void process_job_node_sync(const shared_ptr<TradeJobNode>& job_node);
   void push_job_node(const shared_ptr<TradeJobNode>& job_node) { m_jobqueue.push(job_node); }
   void run();
   double query_net_value(const shared_ptr<DataSlice>& p_data);

public:
   inline void register_portfolio(const shared_ptr<Portfolio>& portfolio) { m_portfolio = weak_ptr<Portfolio>(portfolio); }
   inline void register_brokerage(const shared_ptr<Brokerage>& brokerage) { m_brokerage = weak_ptr<Brokerage>(brokerage); }

private:
   weak_ptr<Portfolio> m_portfolio;
   weak_ptr<Brokerage> m_brokerage;
   BlockingQueue<shared_ptr<TradeJobNode> > m_jobqueue;
   boost::mutex m_cycle_mutex;
   Mode m_mode;
   void do_job();
};

#endif