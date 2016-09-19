#include "stdafx.h"
#include "OHLCVReader_Py.h"
#include "BoostExport.h"
#include <boost/python.hpp>
#include <boost/thread.hpp>
#include "ScopedGILRelease.h"
#include "logger.h"

OHLCVReader_Py::OHLCVReader_Py(const Symbol& symbol)
   : m_symbol(symbol),
   m_pthread()
{
}

OHLCVReader_Py::~OHLCVReader_Py(void)
{
   if(m_pthread != 0)
      m_pthread->join();
}

void OHLCVReader_Py::read()
{
   m_pthread = make_shared<boost::thread>(boost::bind(&OHLCVReader_Py::read_impl, this));
}

void OHLCVReader_Py::read_impl()
{
   try
   {
      ScopedGILAcquire lock;
      initDataFeed();
      object module(handle<>(borrowed(PyImport_AddModule("__main__"))));
      object dictionary = module.attr("__dict__");
      PyRun_SimpleString("execfile('TuShare_OHLCV_day.py')");
      object run(module.attr("run"));
      run(ptr(this));
   }
   catch(error_already_set)
   {
      PyErr_Print();
   }
}

void OHLCVReader_Py::push_data(int open, int high, int low, int close, int adj_close, const boost::posix_time::ptime& starttime, Resolution res, int vol)
{
   Py_BEGIN_ALLOW_THREADS

   auto p_ohlcv = make_shared<OHLCV>(open, high, low, close, adj_close, starttime, res, vol);
   datalog << *p_ohlcv;
   m_queue.push(p_ohlcv);

   Py_END_ALLOW_THREADS
}