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

class PortfolioManager {
public:
    PortfolioManager(shared_ptr<Portfolio> portfolio, shared_ptr<Brokerage> brokerage);

    ~PortfolioManager(void);

public:
    void buy(const boost::posix_time::ptime &time_point, Symbol symbol, double price, double percentage);

    void sell(const boost::posix_time::ptime &time_point, Symbol symbol, double price, double percentage);

    void process_job_node_sync(const shared_ptr<TradeJobNode> &job_node);

    void push_job_node(const shared_ptr<TradeJobNode> &job_node) { _jobqueue.push(job_node); }

    void run();

    bool can_buy();

    bool can_sell(Symbol symbol);

private:
    shared_ptr<Portfolio> _portfolio;
    shared_ptr<Brokerage> _brokerage;
    BlockingQueue<shared_ptr<TradeJobNode> > _jobqueue;
    Mode _mode;

    void do_job();
};

#endif