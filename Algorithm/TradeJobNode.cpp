#include "stdafx.h"
#include "TradeJobNode.h"

TradeJobNode::TradeJobNode(const boost::posix_time::ptime & trade_time, JobType type, Symbol symbol, int shares, double price, double cash)
   :m_trade_time(trade_time),
   m_type(type),
   m_symbol(symbol),
   m_shares(shares),
   m_price(price),
   m_cash(cash)
{
}

TradeJobNode::~TradeJobNode(void)
{
}
