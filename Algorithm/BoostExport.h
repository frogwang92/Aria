#ifndef _BOOSTEXPORT_ALGORITHM_H_
#define _BOOSTEXPORT_ALGORITHM_H_

#include <boost/python.hpp>
#include <datetime.h>
#include "global.h"
#include "Algorithm.h"
#include <boost/date_time.hpp>

using namespace boost;
using namespace boost::python;


BOOST_PYTHON_MODULE(Algorithm)
{
   class_<Algorithm, boost::noncopyable>("Algorithm", no_init)
      .def("buy", &Algorithm::buy)
      .def("sell", &Algorithm::sell)
      ;
   class_<Algorithm_Py, bases<Algorithm> >("Algorithm_Py")
      ;
}

#endif