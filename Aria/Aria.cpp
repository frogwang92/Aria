// Aria.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#ifdef WIN32
#include <Windows.h>
#endif

#include "Singleton.h"

#define INIT_LOG

#include "logger.h"
#include "logger_init.h"
#include "../Engine/RealTimeEngine.h"

using namespace boost;

int main(int argc, char *argv[]) {
    init_log();
    RealTimeEngine engine;

    engine.run();

    logging::core::get()->remove_all_sinks();
    return 0;
}

#undef INIT_LOG