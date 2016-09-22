#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include "global.h"
#include "../Data/Symbol.h"
#include <boost/date_time.hpp>
class DataSlice;
class PortfolioManager;

// This class is exported from the Algorithm.dll
class Algorithm {
public:
	Algorithm(void);
	~Algorithm();

public:
   virtual void on_data(const shared_ptr<DataSlice>& slice) = 0 ;
   virtual void register_call_back(const shared_ptr<PortfolioManager>& portfolio_manager);
   void buy(const boost::posix_time::ptime& time_point, Symbol symbol, double price, double percentage);
   void sell(const boost::posix_time::ptime& time_point, Symbol symbol, double price, double percentage);

private:
   weak_ptr<PortfolioManager> m_portfolio_manager;
};

#endif