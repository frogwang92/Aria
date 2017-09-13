// Algorithm.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Algorithm.h"
#include "PortfolioManager.h"

Algorithm::~Algorithm() {
}

void Algorithm::buy(const boost::posix_time::ptime &time_point, Symbol symbol, double price, double percentage) {
    _portfolio_manager->buy(time_point, symbol, price, percentage);
}

void Algorithm::sell(const boost::posix_time::ptime &time_point, Symbol symbol, double price, double percentage) {
    _portfolio_manager->sell(time_point, symbol, price, percentage);
}