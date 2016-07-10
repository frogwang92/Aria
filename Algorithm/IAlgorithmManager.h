#pragma once
#include "global.h"

class DataSlice;

class IAlgorithmManager
{
public:
   virtual void do_cycle(const shared_ptr<DataSlice>& p_data) = 0;
   virtual void run() = 0;
};