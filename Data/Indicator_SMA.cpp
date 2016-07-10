#include "StdAfx.h"
#include <string>
#include <boost/foreach.hpp>
#include "Indicator_SMA.h"
#include "OHLCV.h"

Indicator_SMA::Indicator_SMA(const Symbol& symbol, const std::string& name, unsigned int period)
   :Indicator(name)
   , m_symbol(symbol)
   , m_period(period)
   , is_warming_up(true)
{
   assert( period != 0 );
}


Indicator_SMA::~Indicator_SMA(void)
{
}

void Indicator_SMA::calculate(boost::shared_ptr<DataSlice> p_dataslice)
{
   shared_ptr<OHLCV> p_data(p_dataslice->get_data(m_symbol));
   double result(0);
   if( p_data == 0 )
      return;
   if( is_warming_up )
   {
      m_data.push_back(p_data->adj_close());
      if(m_data.size() >= m_period)
      {
         is_warming_up = false;
      }
   }
   else
   {
      m_data.pop_front();
      m_data.push_back(p_data->adj_close());
   }

   if(!is_warming_up)
   {
      double sum(0);
      BOOST_FOREACH(double val, m_data)
      {
         sum += val;
      }
      result = sum/m_period;
      p_dataslice->add_indicator(m_symbol, get_name(), result);
   }
}