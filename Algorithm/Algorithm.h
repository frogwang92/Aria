#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include "global.h"
#include "../Data/Symbol.h"
#include <vector>

class PortfolioManager;

// This class is exported from the Algorithm.dll
class Algorithm {

public:
    Algorithm(shared_ptr<PortfolioManager> portfolio_manager) {
        _portfolio_manager = portfolio_manager;
    }

    virtual ~Algorithm();

public:

    virtual void on_data(const std::vector<time_point>& times, const std::vector<price_type> prices) = 0;

    void buy(const boost::posix_time::ptime &time_point, Symbol symbol, double price, double percentage);

    void sell(const boost::posix_time::ptime &time_point, Symbol symbol, double price, double percentage);

protected:
    shared_ptr<PortfolioManager> _portfolio_manager;
};

#endif