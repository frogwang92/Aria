#ifndef _BROKERAGE_H_
#define _BROKERAGE_H_

#include "global.h"
#include "../Data/Symbol.h"
#include <boost/date_time.hpp>

class PortfolioManager;

class Brokerage
{
public:
   Brokerage(void);
   virtual ~Brokerage(void);

public:
   virtual bool request_buy(const boost::posix_time::ptime& time_point, Symbol symbol, double shares, double price) = 0;
   virtual bool request_sell(const boost::posix_time::ptime& time_point, Symbol symbol, double shares, double price) = 0;

   virtual double normalize_buy_shares(double request_cash, double request_price) = 0;
   virtual double normalize_sell_shares(double available_shares, double percentage) = 0;

public:
   inline virtual void register_call_back(PortfolioManager* portfolio_manager) {
       m_portfolio_manager = portfolio_manager;
   }

protected:
   PortfolioManager* m_portfolio_manager;
};

#endif