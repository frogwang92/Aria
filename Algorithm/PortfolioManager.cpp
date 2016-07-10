#include "StdAfx.h"
#include "PortfolioManager.h"
#include <boost/thread.hpp>
#include "Brokerage.h"
#include "Portfolio.h"
#include "TradeJobNode.h"
#include "logger.h"

PortfolioManager::PortfolioManager()
   :m_mode(Backtest)
{
}

PortfolioManager::PortfolioManager(Mode mode)
   :m_mode(mode)
{
}

PortfolioManager::~PortfolioManager(void)
{
}

void PortfolioManager::run()
{
   boost::thread t(boost::bind(&PortfolioManager::do_job, this));
}

void PortfolioManager::buy(Symbol symbol, double price, double percentage)
{
   double cash = m_portfolio.lock()->get_cash_total();
   double cash_available = m_portfolio.lock()->get_cash_available();
   double cash_request = cash * percentage;
   int share = m_brokerage.lock()->normalize_buy_shares(cash_request, price);
   boost::shared_ptr<TradeJobNode> p_node(new TradeJobNode(TradeJobNode::Buy, symbol, share, price, 0));
   if( m_mode == Realtime)
   {
      push_job_node(p_node);
   }
   else   // Backtest
   {
      process_job_node_sync(p_node);
   }
}

void PortfolioManager::sell(Symbol symbol, double price, double percentage)
{
   double shares = m_portfolio.lock()->get_hold_share_available(symbol);
   int request_shares = m_brokerage.lock()->normalize_sell_shares(shares, percentage);
   boost::shared_ptr<TradeJobNode> p_node(new TradeJobNode(TradeJobNode::Sell, symbol, request_shares, price, 0));
   if( m_mode == Realtime)
   {
      push_job_node(p_node);
   }
   else  // Backtest
   {
      process_job_node_sync(p_node);
   }
}

double PortfolioManager::query_net_value(const shared_ptr<DataSlice>& p_data)
{
   return m_portfolio.lock()->query_net_value(p_data);
}

void PortfolioManager::process_job_node_sync(const shared_ptr<TradeJobNode>& p_node)
{
   if(p_node)
   {
      tradelog << *p_node ;
      switch(p_node->get_type())
      {
      case TradeJobNode::Buy:
         m_portfolio.lock()->update_portfolio(p_node->get_shares() * p_node->get_price() * (-1), 
                                          p_node->get_shares() * p_node->get_price(),
                                          p_node->get_symbol(),
                                          0,
                                          0);
         m_brokerage.lock()->request_buy(p_node->get_symbol(), p_node->get_shares(), p_node->get_price());
         break;
      case TradeJobNode::Sell:
         m_portfolio.lock()->update_portfolio(0, 
                                          0,
                                          p_node->get_symbol(),
                                          p_node->get_shares() * (-1),
                                          p_node->get_shares());
         m_brokerage.lock()->request_sell(p_node->get_symbol(), p_node->get_shares(), p_node->get_price());
         break;
      case TradeJobNode::BuyResult:
         m_portfolio.lock()->update_portfolio(0, 
                                       p_node->get_shares() * p_node->get_price() * (-1),
                                       p_node->get_symbol(),
                                       p_node->get_shares(),
                                       0);
         break;
      case TradeJobNode::SellResult:
         m_portfolio.lock()->update_portfolio(p_node->get_shares() * p_node->get_price(), 
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

void PortfolioManager::do_job()
{
   while(true)
   {
      boost::shared_ptr<TradeJobNode> p_node(m_jobqueue.pop());
      process_job_node_sync(p_node);
   }
}
