// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the ENGINE_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// ENGINE_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

#pragma once
#include "global.h"
#include "Singleton.h"
#include <boost/python.hpp>
class IDataFeed;
class IAlgorithmManager;

// This class is exported from the Engine.dll
class ENGINE_API Engine 
{
friend class Singleton<Engine>;

public:
   void run();

   void init();

   ~Engine(void);

private:
	Engine(void);
   
private:
   static boost::shared_ptr<Engine> m_instance;

private:
   PyThreadState* m_thread_state;
   boost::shared_ptr<IDataFeed> m_feed;
   boost::shared_ptr<IAlgorithmManager> m_algorithm_manager;
};
