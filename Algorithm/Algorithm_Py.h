#pragma once
#include "algorithm.h"
#include <boost/python.hpp>

class Algorithm_Py :
   public Algorithm
{
public:
   Algorithm_Py(void);
   virtual ~Algorithm_Py(void);

public:
   void on_data(const shared_ptr<DataSlice>& slice);

private:
   void prepare_py_env();
   boost::python::api::object m_module;
   boost::python::api::object m_dictionary;
   bool m_initialized;
};

