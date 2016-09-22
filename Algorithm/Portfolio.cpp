#include "stdafx.h"
#include "Portfolio.h"
#include "../Data/DataSlice.h"
#include "../Data/OHLCV.h"
#include <iostream>

Portfolio::Portfolio(double init_cash)
   :m_cash(init_cash),
   m_cash_in_freezing(0),
   m_mutex()
{
}

Portfolio::~Portfolio(void)
{
   std::cout << "Portfolio dispose" << std::endl;
}

void Portfolio::update_portfolio(double cash_change, double cash_freezing_change, Symbol symbol, double hold_change, double hold_in_freezing_change)
{
   boost::mutex::scoped_lock lock(m_mutex);

   m_cash += cash_change;
   m_cash_in_freezing += cash_freezing_change;
   m_holds[symbol] += hold_change;
   m_holds_in_freezing[symbol] += hold_in_freezing_change;
}

double Portfolio::get_cash_available()
{
   boost::mutex::scoped_lock lock(m_mutex);
   return m_cash;
}

double Portfolio::get_hold_share_available(Symbol symbol)
{
   boost::mutex::scoped_lock lock(m_mutex);
   std::map<Symbol, double>::iterator iter = m_holds.find(symbol);
   if(iter != m_holds.end())
   {
      return iter->second;
   }
   return 0;
}

double Portfolio::get_cash_in_freezing()
{
   boost::mutex::scoped_lock lock(m_mutex);
   return m_cash_in_freezing;
}

double Portfolio::get_hold_share_in_freezing(Symbol symbol)
{
   boost::mutex::scoped_lock lock(m_mutex);
   std::map<Symbol, double>::iterator iter = m_holds_in_freezing.find(symbol);
   if(iter != m_holds_in_freezing.end())
   {
      return iter->second;
   }
   return 0;
}

double Portfolio::get_cash_total()
{
   boost::mutex::scoped_lock lock(m_mutex);
   return m_cash_in_freezing + m_cash;
}

double Portfolio::get_hold_share_total(Symbol symbol)
{
   boost::mutex::scoped_lock lock(m_mutex);
   std::map<Symbol, double>::iterator iter1 = m_holds.find(symbol);
   std::map<Symbol, double>::iterator iter2 = m_holds_in_freezing.find(symbol);
   double result(0);
   if(iter1 != m_holds.end())
   {
      result += iter1->second;
   }
   if(iter2 != m_holds_in_freezing.end())
   {
      result += iter2->second;
   }
   return result;
}

double Portfolio::query_net_value(const shared_ptr<DataSlice>& p_data)
{
   double result(0);
   for(std::map<Symbol, double>::iterator iter = m_holds.begin(); iter != m_holds.end(); ++iter)
   {
      shared_ptr<OHLCV> p_ohlcv = p_data->get_data(iter->first);
      if(p_ohlcv)
      {
         result += get_hold_share_total(iter->first) * p_ohlcv->adj_close();
      }
   }
   result += get_cash_total();

   return result;
}