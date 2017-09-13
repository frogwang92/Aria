//
// Created by ywang on 6/3/17.
//

#include "RealTimeEngine.h"
#include "../Algorithm/Portfolio.h"
#include "../Algorithm/BacktestBrokerage.h"
#include "../Algorithm/PortfolioManager.h"
#include "../Algorithm/Algo_turtle_intraday.h"

RealTimeEngine::RealTimeEngine()
        : _duration(86400) {
    _pDataFeed = std::make_unique<RealTimeDataFeed>();
}

void RealTimeEngine::init() {
    auto portfolio = std::make_shared<Portfolio>(10000);
    auto brokerage = std::make_shared<BacktestBrokerage>();
    auto portfolioManager = std::make_shared<PortfolioManager>(portfolio, brokerage);
    auto algo = std::make_shared<Algo_turtle_intraday>(portfolioManager);
    portfolioManager->run();
    _pDataFeed->register_algorithm(algo);
}

void RealTimeEngine::run() {
    init();
    _pDataFeed->run();
    sleep(_duration);
}