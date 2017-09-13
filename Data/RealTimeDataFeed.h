//
// Created by ywang on 6/3/17.
//

#ifndef ARIA_REALTIMEDATAFEED_H
#define ARIA_REALTIMEDATAFEED_H

#include "global.h"
#include "../Algorithm/Algorithm.h"
#include "../FIXClient/FIXClientHandler.h"
#include <vector>

class RealTimeDataFeed {
public:
    RealTimeDataFeed();
    RealTimeDataFeed(const RealTimeDataFeed& rhs) = delete;
    RealTimeDataFeed& operator=(const RealTimeDataFeed& rhs) = delete;
    ~RealTimeDataFeed() = default;
    void run();
    void register_algorithm(shared_ptr<Algorithm> pAlgo) {
        _pAlgo = pAlgo;
    }

private:
    void on_data(time_point time, price_type price, double vol);

private:
    std::vector<time_point> times;
    std::vector<price_type> prices;

    unique_ptr<FIXClientHandler> _pHandler;

    shared_ptr<Algorithm> _pAlgo;
};


#endif //ARIA_REALTIMEDATAFEED_H
