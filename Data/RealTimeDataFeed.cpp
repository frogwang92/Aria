//
// Created by ywang on 6/3/17.
//

#include <logger.h>
#include "RealTimeDataFeed.h"

RealTimeDataFeed::RealTimeDataFeed() {
    _pHandler = std::make_unique<FIXClientHandler>("OKCoinFIX.cfg");
    _pHandler->register_callback(std::bind(&RealTimeDataFeed::on_data, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

void RealTimeDataFeed::run() {
    _pHandler->run();
}

void RealTimeDataFeed::on_data(time_point time, price_type price, double vol) {
    times.push_back(time);
    prices.push_back(price);

    datalog << to_simple_string(time) << "," << price;

    if(_pAlgo) {
        _pAlgo->on_data(times, prices);
    }
}