#include "stdafx.h"
#include "BacktestBrokerage.h"
#include "TradeJobNode.h"
#include "PortfolioManager.h"

BacktestBrokerage::BacktestBrokerage(void)
{
}


BacktestBrokerage::~BacktestBrokerage(void)
{
}

bool BacktestBrokerage::request_buy(const boost::posix_time::ptime& time_point, Symbol symbol, double shares, double price)
{
   shared_ptr<TradeJobNode> p_node(new TradeJobNode(time_point, TradeJobNode::BuyResult, symbol, shares, price, 0));
   
   m_portfolio_manager->process_job_node_sync(p_node);
   return true;
}

bool BacktestBrokerage::request_sell(const boost::posix_time::ptime& time_point, Symbol symbol, double shares, double price)
{
   shared_ptr<TradeJobNode> p_node(new TradeJobNode(time_point, TradeJobNode::SellResult, symbol, shares, price, 0));
   m_portfolio_manager->process_job_node_sync(p_node);
   return true;
}

double BacktestBrokerage::normalize_buy_shares(double request_cash, double request_price)
{
   if(request_price != 0)
   {
      return request_cash/request_price;
   }
   return 0;
}

double BacktestBrokerage::normalize_sell_shares(double available_shares, double percentage)
{
   return available_shares * percentage;
}