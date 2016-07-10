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

void Algorithm::buy(Symbol symbol, double price, double percentage)
{
   (m_portfolio_manager.lock())->buy(symbol, price, percentage);
}

void Algorithm::sell(Symbol symbol, double price, double percentage)
{
   (m_portfolio_manager.lock())->sell(symbol, price, percentage);
}