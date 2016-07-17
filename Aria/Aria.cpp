// Aria.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include "Singleton.h"
#define INIT_LOG
#include "logger.h"
#include "logger_init.h"
#include <boost/date_time.hpp>
#include "../Engine/Engine.h"
#include "../Data/Resolution.h"

using namespace boost;

int _tmain(int argc, _TCHAR* argv[])
{
   init_log();
   posix_time::ptime start(boost::gregorian::date(2005, 02, 01));

   Singleton<Engine>::instance().init_back_test(start, Day);
   Singleton<Engine>::instance().run();
   
   _tsystem(_T("pause"));
   logging::core::get()->remove_all_sinks();
	return 0;
}

#undef INIT_LOG