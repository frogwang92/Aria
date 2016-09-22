#include "stdafx.h"
#include "Singleton.h"
#include "AlgorithmInitializer.h"
#include "Portfolio.h"
#include "BacktestBrokerage.h"
#include "PortfolioManager.h"
#include "AlgorithmManager.h"
#include "Algorithm_Buyandhold.h"
#include <boost/date_time.hpp>
#include "Algorithm_Py.h"

using namespace boost::posix_time;

AlgorithmInitializer::AlgorithmInitializer(void)
{
}

shared_ptr<IAlgorithmManager> AlgorithmInitializer::init()
{
   ptime start(boost::gregorian::date(2005, 02, 01));

   shared_ptr<Portfolio> p_portfolio(new Portfolio(10000000));
   shared_ptr<Brokerage> p_brokerage(new BacktestBrokerage());
   //shared_ptr<Algorithm> p_algo(new Algorithm_Buyandhold(start, Symbol(600000)));
   shared_ptr<Algorithm> p_algo(new Algorithm_Py());

   shared_ptr<AlgorithmManager> p_manager(new AlgorithmManager(p_brokerage, p_algo, p_portfolio));
   p_manager->init();
   return p_manager;
}