#pragma once
#ifdef DATA_EXPORTS
#define DATA_API __declspec(dllexport)
#else
#define DATA_API __declspec(dllimport)
#endif

#include "global.h"
#include "Singleton.h"

class IDataFeed;

class DATA_API DataInitializer
{
friend class Singleton<DataInitializer>;

public:
   boost::shared_ptr<IDataFeed> init();

protected:
   DataInitializer(void);

};

