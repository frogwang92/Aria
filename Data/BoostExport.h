#ifndef _BOOSTEXPORT_H_
#define _BOOSTEXPORT_H_

#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/date_time.hpp>
#include <datetime.h>
#include "global.h"
#include "Symbol.h"
#include "OHLCV.h"
#include "Resolution.h"
#include "DataSlice.h"
#include "OHLCVReader_Py.h"

using namespace boost;
using namespace boost::python;

struct ptime_from_python_datetime_str
{
   static void* convertible(PyObject* obj_ptr)
   {
      if(!PyString_Check(obj_ptr)) return 0;
      return obj_ptr;
   }

   static void construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data)
   {
      const char* value = PyString_AsString(obj_ptr);
      if(value == 0) boost::python::throw_error_already_set();
      void* storage = ((boost::python::converter::rvalue_from_python_storage<boost::posix_time::ptime>*)data)->storage.bytes;
      boost::posix_time::ptime t(boost::posix_time::time_from_string(value));
      new (storage) boost::posix_time::ptime(boost::posix_time::time_from_string(value));
      data->convertible = storage;
   }

   ptime_from_python_datetime_str()
   {
      boost::python::converter::registry::push_back(
         convertible, &construct, boost::python::type_id<boost::posix_time::ptime>() );
   }
};

static long get_usecs(boost::posix_time::time_duration const& d)
{
   static long resolution = (long)boost::posix_time::time_duration::ticks_per_second();
   long fracsecs = (long)d.fractional_seconds();
   if(resolution > 1000000)
      return fracsecs / ( resolution / 1000000);
   else
      return fracsecs * ( resolution / 1000000);
}

struct ptime_to_python
{
   static PyObject* convert(boost::posix_time::ptime const & pt)
   {
      boost::gregorian::date date = pt.date();
      boost::posix_time::time_duration td = pt.time_of_day();

      return PyDateTime_FromDateAndTime(
         (int)date.year(),
         (int)date.month(),
         (int)date.day(),
         td.hours(),
         td.minutes(),
         td.seconds(),
         get_usecs(td)
         );
   }
};

BOOST_PYTHON_MODULE(DataFeed)
{
   PyDateTime_IMPORT;
   ptime_from_python_datetime_str();
   to_python_converter<const boost::posix_time::ptime, ptime_to_python>();
    register_ptr_to_python<std::shared_ptr<DataSlice> >();
    register_ptr_to_python<std::shared_ptr<OHLCVReader_Py> >();
    register_ptr_to_python<std::shared_ptr<OHLCV> >();

   enum_<Resolution>("Resolution")
      .value("Second", Second)
      .value("FiveSeconds",FiveSeconds)
      .value("TenSeconds",TenSeconds)
      .value("Minute", Minute)
      .value("FiveMinutes", FiveMinutes)
      .value("Hour", Hour)
      .value("TwoHours",TwoHours)
      .value("Day",Day)
      ;
   class_<OHLC>("OHLC")
      .def("open", &OHLC::open)
      .def("close", &OHLC::close)
      .def("high", &OHLC::high)
      .def("low", &OHLC::low)
      .def("adj_close", &OHLC::adj_close)
      .def("start_time", &OHLC::start_time, return_value_policy<return_by_value>() )
      .def("end_time", &OHLC::end_time, return_value_policy<return_by_value>() )
      ;
   class_<OHLCV, bases<OHLC> >("OHLCV")
      .def("volume", &OHLCV::volume)
      ;
   class_<Symbol>("Symbol", init<int>())
      .def("get_code", &Symbol::get_code)
      ;
   class_<DataSlice>("DataSlice")
      .def("get_resolution", &DataSlice::get_resolution)
      .def("get_data", &DataSlice::get_data)
      .def("get_start_time", &DataSlice::get_start_time, return_value_policy<return_by_value>() )
      .def("get_end_time", &DataSlice::get_end_time, return_value_policy<return_by_value>() )
      ;
   class_<OHLCVReader_Py, boost::noncopyable>("OHLCVReader_Py", no_init)
      .def("push_data", &OHLCVReader_Py::push_data)
      ;
   
}

#endif