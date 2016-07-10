#pragma once
#include "../Common/global.h"
#include "../Data/Symbol.h"

class PortfolioManager;

class Brokerage
{
public:
   Brokerage(void);
   virtual ~Brokerage(void);

public:
   virtual bool request_buy(Symbol symbol, double shares, double price) = 0;
   virtual bool request_sell(Symbol symbol, double shares, double price) = 0;

   virtual int normalize_buy_shares(double request_cash, double request_price) = 0;
   virtual int normalize_sell_shares(double available_shares, double percentage) = 0;

public:
   inline virtual void register_call_back(const shared_ptr<PortfolioManager>& portfolio_manager) { m_portfolio_manager = weak_ptr<PortfolioManager>(portfolio_manager); }

protected:
   weak_ptr<PortfolioManager> m_portfolio_manager;
};

