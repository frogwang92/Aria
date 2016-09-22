#ifndef _ALGORITHM_INITIALIZER_H_
#define _ALGORITHM_INITIALIZER_H_

#include "Common.h"  

#ifdef ALGORITHM_EXPORTS  
#define ALGORITHM_CLASS DLL_EXPORT_CLASS_DECL  
#define ALGORITHM_API DLL_EXPORT_DECL  
#else  
#define ALGORITHM_CLASS DLL_IMPORT_CLASS_DECL  
#define ALGORITHM_API DLL_IMPORT_DECL  
#endif  

#include "global.h"

class IAlgorithmManager;

class ALGORITHM_CLASS AlgorithmInitializer
{

friend class Singleton<AlgorithmInitializer>;

public:
   shared_ptr<IAlgorithmManager> init();

private:
   AlgorithmInitializer(void);

};

#endif