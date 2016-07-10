#include "StdAfx.h"
#include <boost/python.hpp>
#include "Algorithm_Py.h"
#include "BoostExport.h"
#include "ScopedGILRelease.h"

Algorithm_Py::Algorithm_Py(void)
   :m_initialized(false)
{
}


Algorithm_Py::~Algorithm_Py(void)
{
}

void Algorithm_Py::on_data(const shared_ptr<DataSlice>& slice)
{
   if( !m_initialized )
   {
      // prepare python enviroment here
      // datafeed is initialized before on_data is called
      prepare_py_env();
      m_initialized = true;
   }
   try
   {
      ScopedGILAcquire lock;
      object on_data(m_module.attr("on_data"));
      on_data(ptr(this), slice);
   }
   catch(error_already_set)
   {
      PyErr_Print();
   }
}

void Algorithm_Py::prepare_py_env()
{
   try
   {
      ScopedGILAcquire lock;
      initAlgorithm();
      m_module = object(handle<>(borrowed(PyImport_AddModule("__main__"))));
      m_dictionary = m_module.attr("__dict__");
      
      PyRun_SimpleString("execfile('Algorithm_Buyandhold_Py.py')");
   }
   catch(error_already_set)
   {
      PyErr_Print();
   }
}