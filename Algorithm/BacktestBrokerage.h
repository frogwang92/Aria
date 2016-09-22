#ifndef _BACKTEST_BROKERAGE_H_
#define _BACKTEST_BROKERAGE_H_

#include "Brokerage.h"

class BacktestBrokerage :
   public Brokerage
{
public:
   BacktestBrokerage(void);
   ~BacktestBrokerage(void);

public:
   virtual bool request_buy(const boost::posix_time::ptime& time_point, Symbol symbol, double shares, double price);
   virtual bool request_sell(const boost::posix_time::ptime& time_point, Symbol symbol, double shares, double price);

   virtual int normalize_buy_shares(double request_cash, double request_price);
   virtual int normalize_sell_shares(double available_shares, double percentage);
};

#endif