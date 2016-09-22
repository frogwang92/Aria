#ifndef _ALGORITHM_MANAGER_H_
#define _ALGORITHM_MANAGER_H_

#include "global.h"
#include "IAlgorithmManager.h"

class Algorithm;
class Portfolio;
class Brokerage;
class PortfolioManager;

class AlgorithmManager
   :public IAlgorithmManager
{

friend class PortfolioManager;
friend class Brokerage;

public:
   AlgorithmManager(const shared_ptr<Brokerage>& brokerage, const shared_ptr<Algorithm>& algorithm, const shared_ptr<Portfolio>& portfolio);
   ~AlgorithmManager(void);
   
   void run();
   void do_cycle(const shared_ptr<DataSlice>& p_data);

public:
   void init();

private:
   shared_ptr<Brokerage> m_brokerage;
   shared_ptr<Algorithm> m_algorithm;
   shared_ptr<Portfolio> m_portfolio;

   shared_ptr<PortfolioManager> m_portfolio_manager;

   bool m_active;
};

#endif