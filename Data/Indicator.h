#ifndef _INDICATOR_H_
#define _INDICATOR_H_

#include "global.h"
#include "DataSlice.h"
#include <string>

class Indicator
{
public:
   explicit Indicator(const std::string& name);

   virtual ~Indicator(void);

public:
    virtual void calculate(shared_ptr<DataSlice> p_dataslice) = 0;
   const std::string& get_name() { return m_name; }

private:
   std::string m_name;
};

#endif