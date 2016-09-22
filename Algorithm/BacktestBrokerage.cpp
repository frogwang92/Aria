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
   
   m_portfolio_manager.lock()->process_job_node_sync(p_node);
   return true;
}

bool BacktestBrokerage::request_sell(const boost::posix_time::ptime& time_point, Symbol symbol, double shares, double price)
{
   shared_ptr<TradeJobNode> p_node(new TradeJobNode(time_point, TradeJobNode::SellResult, symbol, shares, price, 0));
   m_portfolio_manager.lock()->process_job_node_sync(p_node);
   return true;
}

int BacktestBrokerage::normalize_buy_shares(double request_cash, double request_price)
{
   if(request_price != 0)
   {
      return ((int)(request_cash/request_price))/100 * 100;
   }
   return 0;
}

int BacktestBrokerage::normalize_sell_shares(double available_shares, double percentage)
{
   return (int)(available_shares * percentage);
   return 0;
}