#include "StdAfx.h"
#include "TradeJobNode.h"


TradeJobNode::TradeJobNode(JobType type, Symbol symbol, int share, double price, double cash)
   :m_type(type),
   m_symbol(symbol),
   m_shares(share),
   m_price(price),
   m_cash(cash)
{
}


TradeJobNode::~TradeJobNode(void)
{
}
