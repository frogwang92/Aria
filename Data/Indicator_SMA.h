#pragma once
#ifndef _INDICATOR_SMA_H_
#define _INDICATOR_SMA_H_

#include "Indicator.h"
#include <deque>
#include "Symbol.h"

class Indicator_SMA :
   public Indicator
{
public:
   Indicator_SMA(const Symbol& symbol, const std::string& name, unsigned int period);
   ~Indicator_SMA(void);

public:
   virtual void calculate(boost::shared_ptr<DataSlice> p_dataslice);

private:
   unsigned int m_period;
   std::deque<double> m_data;
   Symbol m_symbol;
   bool is_warming_up;
};

#endif