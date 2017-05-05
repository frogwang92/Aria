#ifndef _DATAINITIALIZER_H_
#define _DATAINITIALIZER_H_

#include "Common.h"  

#ifdef DATA_EXPORTS  
#define DATA_CLASS DLL_EXPORT_CLASS_DECL  
#define DATA_API DLL_EXPORT_DECL  
#else  
#define DATA_CLASS DLL_IMPORT_CLASS_DECL  
#define DATA_API DLL_IMPORT_DECL  
#endif 

#include "global.h"
#include "Singleton.h"

class IDataFeed;

class DATA_CLASS DataInitializer
{
friend class Singleton<DataInitializer>;

public:
    shared_ptr<IDataFeed> init();

protected:
   DataInitializer(void);

};

#endif