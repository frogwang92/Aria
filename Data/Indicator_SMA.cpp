
#include <string>
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

void Indicator_SMA::calculate(shared_ptr<DataSlice> p_dataslice)
{
   auto p_data(p_dataslice->get_data(m_symbol));
   auto result = 0.0;
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
      auto sum = 0.0;
      for(auto val: m_data)
      {
         sum += val;
      }
      result = sum/m_period;
      p_dataslice->add_indicator(m_symbol, get_name(), result);
   }
}