#pragma once
#ifdef ALGORITHM_EXPORTS
#define ALGORITHM_API __declspec(dllexport)
#else
#define ALGORITHM_API __declspec(dllimport)
#endif

#include "global.h"
class IAlgorithmManager;

class ALGORITHM_API AlgorithmInitializer
{

friend class Singleton<AlgorithmInitializer>;

public:
   shared_ptr<IAlgorithmManager> init();

private:
   AlgorithmInitializer(void);

};

