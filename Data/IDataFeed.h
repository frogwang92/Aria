#pragma once
#include "../Common/global.h"

class DataSlice;

class IDataFeed
{
public:
   virtual bool operator>> (shared_ptr<DataSlice>& p_data) = 0;
};