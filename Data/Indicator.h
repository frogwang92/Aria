#pragma once
#include "DataSlice.h"
#include <string>
#include <boost/shared_ptr.hpp>

class Indicator
{
public:
   explicit Indicator(const std::string& name);

   virtual ~Indicator(void);

public:
   virtual void calculate(boost::shared_ptr<DataSlice> p_dataslice) = 0;
   const std::string& get_name() { return m_name; }

private:
   std::string m_name;
};

