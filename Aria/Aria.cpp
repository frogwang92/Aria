// Aria.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include "Singleton.h"
#define INIT_LOG
#include "logger.h"
#include "logger_init.h"

#include "../Engine/Engine.h"

int _tmain(int argc, _TCHAR* argv[])
{
   init_log();

   Singleton<Engine>::instance().init();
   Singleton<Engine>::instance().run();
   
   _tsystem(_T("pause"));
   logging::core::get()->remove_all_sinks();
	return 0;
}

#undef INIT_LOG