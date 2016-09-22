#pragma once
#ifndef _IDATAFEED_H_
#define _IDATAFEED_H_

#include "global.h"

class DataSlice;

class IDataFeed
{
public:
   virtual bool operator>> (shared_ptr<DataSlice>& p_data) = 0;
   virtual shared_ptr<DataSlice> head() = 0;
};

#endif