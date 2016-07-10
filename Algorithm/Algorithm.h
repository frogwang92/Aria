#pragma once
#include "global.h"
#include "../Data/Symbol.h"

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
   void buy(Symbol symbol, double price, double percentage);
   void sell(Symbol symbol, double price, double percentage);

private:
   weak_ptr<PortfolioManager> m_portfolio_manager;
};

