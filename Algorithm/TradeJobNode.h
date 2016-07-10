#pragma once
#include "../Data/Symbol.h"
#include <iostream>

class TradeJobNode
{
public:
   enum JobType { Buy, Sell, BuyResult, SellResult };

public:
   TradeJobNode(JobType type, Symbol symbol, int shares, double price, double cash);
   ~TradeJobNode(void);

public:
   JobType get_type() const { return m_type; }
   Symbol get_symbol() const { return m_symbol; }
   int get_shares() const { return m_shares; }
   double get_price() const { return m_price; }
   double get_cash() const { return m_cash; }

private:
   JobType m_type;
   Symbol m_symbol;
   int m_shares;
   double m_price;
   double m_cash;
};

using std::ostream;

inline ostream& operator<< ( ostream& os, const TradeJobNode& tradenode)
{
   return os << tradenode.get_type() << ":" 
      << tradenode.get_symbol() << "," 
      << tradenode.get_shares() << ","
      << tradenode.get_price() << ","
      << tradenode.get_cash();
}