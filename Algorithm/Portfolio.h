#ifndef _PORTFOLIO_H_
#define _PORTFOLIO_H_

#include "global.h"
#include <map>
#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include "../Data/Symbol.h"

class DataSlice;

class Portfolio
   : public boost::noncopyable
{
public:
   explicit Portfolio(double init_cash);
   ~Portfolio(void);

public:
   void update_portfolio(double cash_change, double cash_freezing_change, Symbol symbol, double hold_change, double hold_in_freezing_change);
   double get_cash_available();
   double get_hold_share_available(Symbol symbol);
   double get_cash_in_freezing();
   double get_hold_share_in_freezing(Symbol symbol);
   double get_cash_total();
   double get_hold_share_total(Symbol symbol);
   double query_net_value(const shared_ptr<DataSlice>& p_data);

private:
   double m_cash;
   std::map<Symbol, double> m_holds;
   double m_cash_in_freezing;
   std::map<Symbol, double> m_holds_in_freezing;

   boost::mutex m_mutex;
};

#endif