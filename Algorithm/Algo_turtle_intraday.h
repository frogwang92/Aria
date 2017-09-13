//
// Created by ywang on 6/4/17.
//

#ifndef ARIA_ALGO_TURTLE_INTRADAY_H
#define ARIA_ALGO_TURTLE_INTRADAY_H

#include "Algorithm.h"
#include <stdexcept>

class Algo_turtle_intraday : public Algorithm {

public:
    Algo_turtle_intraday(shared_ptr<PortfolioManager> portfolio_manager);

    virtual void on_data(const std::vector<time_point> &times, const std::vector<price_type> prices);

private:
    time_duration _long_period;
    time_duration _short_period;
    bool _is_warming_up;
    time_duration _warm_up_period;
private:
    static const Symbol sym;
    constexpr static const double tolerance_high = 1.001;  // 0.1%
    constexpr static const double tolerance_low  = 0.999;
};


#endif //ARIA_ALGO_TURTLE_INTRADAY_H
