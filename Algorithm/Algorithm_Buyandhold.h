#pragma once
#include "global.h"
#include "algorithm.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include "../Data/Symbol.h"
class Algorithm_Buyandhold :
   public Algorithm
{
public:
   Algorithm_Buyandhold(const boost::posix_time::ptime& start_time, Symbol symbol);
   ~Algorithm_Buyandhold(void);

public:
   void on_data(const shared_ptr<DataSlice>& slice);

private:
   boost::posix_time::ptime m_start_time;
   Symbol m_symbol;
   bool m_bought;
};

