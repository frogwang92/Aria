// Engine.cpp : Defines the exported functions for the DLL application.
//

#include <iostream>

#include "global.h"
#include "Singleton.h"
#include "Engine.h"
#include "../Data/DataInitializer.h"
#include "../Algorithm/AlgorithmInitializer.h"
#include "../Algorithm/IAlgorithmManager.h"
#include "../Data/IDataFeed.h"
#include "../Data/DataSlice.h"
#include "BacktestTimeHandler.h"
#include "TimeService.h"
#include "Scheduler.h"

// This is the constructor of a class that has been exported.
// see Engine.h for the class definition
Engine::Engine()
   :m_feed(),
   m_algorithm_manager(),
   m_mode(Backtest),
   m_res(Day)
{
   Py_Initialize();
   PyEval_InitThreads();
   m_thread_state = PyEval_SaveThread();
}

void Engine::init_back_test(boost::posix_time::ptime start_time, Resolution res)
{
   m_pTimeHandler = shared_ptr<IMasterTimeHandler>(new BacktestTimeHandler(start_time, Day));
   Singleton<TimeService>::instance().register_handler(m_pTimeHandler);
   std::function<bool()> task = std::bind(&Engine::do_cycle, this);
   m_pScheduler = shared_ptr<Scheduler>(new Scheduler(start_time, duration(res), task));
   init();
}

Engine::~Engine()
{
   PyEval_RestoreThread(m_thread_state);
   Py_Finalize();
}

void Engine::init()
{
   m_feed = Singleton<DataInitializer>::instance().init();
   m_algorithm_manager = Singleton<AlgorithmInitializer>::instance().init();
}

// this guy is running in main thread
void Engine::run()
{
   assert(m_feed != 0);
   assert(m_algorithm_manager !=0);

   m_algorithm_manager->run();

   m_pScheduler->run();
}

bool Engine::do_cycle()
{
   if (m_feed->head()->get_start_time() <= TimeService::now())
   {
       shared_ptr<DataSlice> p_data;
      if ((*m_feed) >> p_data)
      {
         m_algorithm_manager->do_cycle(p_data);
      }
      else
      {
         return false;
      }
   }
    std::dynamic_pointer_cast<BacktestTimeHandler>(m_pTimeHandler)->step();
   return true;
}