//
// Created by ywang on 6/4/17.
//

#include "Algo_turtle_intraday.h"
#include "PortfolioManager.h"
#include "TimeService.h"

const Symbol Algo_turtle_intraday::sym = Symbol(BTC);

Algo_turtle_intraday::Algo_turtle_intraday(shared_ptr<PortfolioManager> portfolio_manager)
        : Algorithm(portfolio_manager),
          _long_period(0, 0, 50), _short_period(0, 0, 20), _is_warming_up(true), _warm_up_period(_long_period){
}

void Algo_turtle_intraday::on_data(const std::vector<time_point>& times, const std::vector<price_type> prices) {
    auto t = times.back();
    auto p = prices.back();

    if (( t - times.front() ) > _warm_up_period ) {
        _is_warming_up = false;
    }
    else {
        return;
    }

    auto first_time_at_long_period =
            std::find_if(times.begin(), times.end(), [t, this](time_point ti){return ti >= (t - this->_long_period); });

    auto first_price_at_long_period = prices.begin() + (first_time_at_long_period - times.begin());

    auto p_high = std::max_element(first_price_at_long_period, prices.end() - 1);

    if (p > (*p_high)* Algo_turtle_intraday::tolerance_high ) {
        if ( _portfolio_manager->can_buy() ) {
            buy(t, Algo_turtle_intraday::sym, p, 1);
        }
    }

    auto first_time_at_short_period =
            std::find_if(times.begin(), times.end(), [t, this](time_point ti){return ti >= (t - this->_short_period); });

    auto first_price_at_short_period = prices.begin() + (first_time_at_short_period - times.begin());

    auto p_low = std::min_element(first_price_at_short_period, prices.end() - 1);

    if (p < (*p_low) * Algo_turtle_intraday::tolerance_low) {
        if ( _portfolio_manager->can_sell(Algo_turtle_intraday::sym) ) {
            sell(t, Algo_turtle_intraday::sym, p, 1);
        }
    }
}