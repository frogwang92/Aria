// Algorithm.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Algorithm.h"
#include "PortfolioManager.h"

// This is the constructor of a class that has been exported.
// see Algorithm.h for the class definition
Algorithm::Algorithm()
{
	return;
}

Algorithm::~Algorithm()
{
}

void Algorithm::register_call_back(const shared_ptr<PortfolioManager>& portfolio_manager)
{
   m_portfolio_manager = weak_ptr<PortfolioManager>(portfolio_manager);
}

void Algorithm::buy(const boost::posix_time::ptime& time_point, Symbol symbol, double price, double percentage)
{
   (m_portfolio_manager.lock())->buy(time_point, symbol, price, percentage);
}

void Algorithm::sell(const boost::posix_time::ptime& time_point, Symbol symbol, double price, double percentage)
{
   (m_portfolio_manager.lock())->sell(time_point, symbol, price, percentage);
}