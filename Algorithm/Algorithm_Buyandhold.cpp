#include "StdAfx.h"
#include "Algorithm_Buyandhold.h"
#include "../Data/DataSlice.h"
#include "../Data/OHLCV.h"

Algorithm_Buyandhold::Algorithm_Buyandhold(const boost::posix_time::ptime& start_time, Symbol symbol)
   :m_start_time(start_time),
   m_symbol(symbol),
   m_bought(false)
{
}


Algorithm_Buyandhold::~Algorithm_Buyandhold(void)
{
}

void Algorithm_Buyandhold::on_data(const shared_ptr<DataSlice>& slice)
{
   if( m_start_time >= slice->get_start_time() && !m_bought)
   {
      buy(m_symbol, slice->get_data(m_symbol)->adj_close(), 1.0);
      m_bought = true;
   }
}