#pragma once

#include "global.h"
#include <boost/make_shared.hpp>
#include <boost/thread/thread.hpp>
#include <boost/log/core.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/formatter_parser.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/severity_feature.hpp>
#include <fstream>

namespace logging = boost::log;
namespace attrs   = boost::log::attributes;
namespace src     = boost::log::sources;
namespace sinks   = boost::log::sinks;
namespace expr    = boost::log::expressions;
namespace keywords = boost::log::keywords;

enum sign_severity_level
{
   trade,
   portfolio,
   data,
   info,
   debug,
   trace,
   warning,
   error
};

BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(my_logger, src::severity_logger_mt<sign_severity_level>)

#define debuglog BOOST_LOG_SEV(my_logger::get(), debug)
#define trclog BOOST_LOG_SEV(my_logger::get(), trace)
#define warninglog BOOST_LOG_SEV(my_logger::get(), warning)
#define errlog BOOST_LOG_SEV(my_logger::get(), error)
#define tradelog BOOST_LOG_SEV(my_logger::get(), trade)
#define portfoliolog BOOST_LOG_SEV(my_logger::get(), portfolio)
#define datalog BOOST_LOG_SEV(my_logger::get(), data)