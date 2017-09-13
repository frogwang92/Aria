
#include "PortfolioManager.h"
#include <boost/thread.hpp>
#include "Brokerage.h"
#include "Portfolio.h"
#include "TradeJobNode.h"
#include "logger.h"

PortfolioManager::PortfolioManager(shared_ptr<Portfolio> portfolio,shared_ptr<Brokerage> brokerage)
        : _portfolio(portfolio), _brokerage(brokerage), _mode(Backtest) {
    _brokerage->register_call_back(this);
}

PortfolioManager::~PortfolioManager(void) {
}

void PortfolioManager::run() {
    boost::thread t(boost::bind(&PortfolioManager::do_job, this));
}

void PortfolioManager::buy(const boost::posix_time::ptime &time_point, Symbol symbol, double price, double percentage) {
    double cash = _portfolio->get_cash_total();
    double cash_available = _portfolio->get_cash_available();
    double cash_request = cash * percentage;
    double share = _brokerage->normalize_buy_shares(cash_request, price);
    shared_ptr<TradeJobNode> p_node(new TradeJobNode(time_point, TradeJobNode::Buy, symbol, share, price, 0));
    if (_mode == Realtime) {
        push_job_node(p_node);
    } else   // Backtest {
        process_job_node_sync(p_node);
}

void
PortfolioManager::sell(const boost::posix_time::ptime &time_point, Symbol symbol, double price, double percentage) {
    double shares = _portfolio->get_hold_share_available(symbol);
    double request_shares = _brokerage->normalize_sell_shares(shares, percentage);
    shared_ptr<TradeJobNode> p_node(new TradeJobNode(time_point, TradeJobNode::Sell, symbol, request_shares, price, 0));
    if (_mode == Realtime) {
        push_job_node(p_node);
    } else  // Backtest {
        process_job_node_sync(p_node);
}

void PortfolioManager::process_job_node_sync(const shared_ptr<TradeJobNode> &p_node) {
    if (p_node) {
        tradelog << to_iso_extended_string(p_node->get_trade_time().date()) << "," << *p_node;
        switch (p_node->get_type()) {
            case TradeJobNode::Buy:
                _portfolio->update_portfolio(p_node->get_shares() * p_node->get_price() * (-1),
                                             p_node->get_shares() * p_node->get_price(),
                                             p_node->get_symbol(),
                                             0,
                                             0);
                _brokerage->request_buy(p_node->get_trade_time(), p_node->get_symbol(), p_node->get_shares(),
                                        p_node->get_price());
                break;
            case TradeJobNode::Sell:
                _portfolio->update_portfolio(0,
                                             0,
                                             p_node->get_symbol(),
                                             p_node->get_shares() * (-1),
                                             p_node->get_shares());
                _brokerage->request_sell(p_node->get_trade_time(), p_node->get_symbol(), p_node->get_shares(),
                                         p_node->get_price());
                break;
            case TradeJobNode::BuyResult:
                _portfolio->update_portfolio(0,
                                             p_node->get_shares() * p_node->get_price() * (-1),
                                             p_node->get_symbol(),
                                             p_node->get_shares(),
                                             0);
                break;
            case TradeJobNode::SellResult:
                _portfolio->update_portfolio(p_node->get_shares() * p_node->get_price(),
                                             0,
                                             p_node->get_symbol(),
                                             0,
                                             p_node->get_shares() * (-1));
                break;
            default:
                break;
        }
    }
}

void PortfolioManager::do_job() {
    while (true) {
        shared_ptr<TradeJobNode> p_node(_jobqueue.pop());
        process_job_node_sync(p_node);
    }
}

bool PortfolioManager::can_buy() {
    return _portfolio->get_cash_available() > 0;
}

bool PortfolioManager::can_sell(Symbol symbol) {
    return _portfolio->get_hold_share_available(symbol) > 0;
}

