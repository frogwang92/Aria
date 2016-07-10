#pragma once
#include "brokerage.h"

class BacktestBrokerage :
   public Brokerage
{
public:
   BacktestBrokerage(void);
   ~BacktestBrokerage(void);

public:
   virtual bool request_buy(Symbol symbol, double shares, double price);
   virtual bool request_sell(Symbol symbol, double shares, double price);

   virtual int normalize_buy_shares(double request_cash, double request_price);
   virtual int normalize_sell_shares(double available_shares, double percentage);
};

