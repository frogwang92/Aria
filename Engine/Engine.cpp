// Engine.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <iostream>

#include "global.h"
#include "Singleton.h"
#include "Engine.h"
#include "../data/DataInitializer.h"
#include "../Algorithm/AlgorithmInitializer.h"
#include "../Algorithm/IAlgorithmManager.h"
#include "../Data/IDataFeed.h"
#include "../Common/ScopedGILRelease.h"

using namespace boost;

// This is the constructor of a class that has been exported.
// see Engine.h for the class definition
Engine::Engine()
   :m_feed(),
   m_algorithm_manager()
{
   Py_Initialize();
   PyEval_InitThreads();
   m_thread_state = PyEval_SaveThread();
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

   while( true )
   {
      boost::shared_ptr<DataSlice> p_data;
      if( (*m_feed) >> p_data )
      {
         m_algorithm_manager->do_cycle(p_data);
      }
      else
      {
         break;
      }
   }
}