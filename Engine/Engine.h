#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "Common.h"  

#ifdef ENGINE_EXPORTS  
#define ENGINE_CLASS DLL_EXPORT_CLASS_DECL  
#define ENGINE_API DLL_EXPORT_DECL  
#else  
#define ENGINE_CLASS DLL_IMPORT_CLASS_DECL  
#define ENGINE_API DLL_IMPORT_DECL  
#endif 

#include "global.h"
#include "Singleton.h"
#include <boost/python.hpp>
#include <boost/date_time.hpp>
#include "mode.h"
#include "../Data/Resolution.h"

class IMasterTimeHandler;
class IDataFeed;
class IAlgorithmManager;
class Scheduler;

// This class is exported from the Engine.dll
class ENGINE_CLASS Engine 
{
friend class Singleton<Engine>;

public:
   void run();

   void init_back_test(boost::posix_time::ptime start_time, Resolution res);

   ~Engine(void);

private:
	Engine(void);
   void init();

private:
	static shared_ptr<Engine> m_instance;

private:
   PyThreadState* m_thread_state;
	shared_ptr<IDataFeed> m_feed;
	shared_ptr<IAlgorithmManager> m_algorithm_manager;
	shared_ptr<IMasterTimeHandler> m_pTimeHandler;
	shared_ptr<Scheduler> m_pScheduler;

   Mode m_mode;
   Resolution m_res;

   bool do_cycle();
};

#endif