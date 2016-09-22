#ifndef _GLOBAL_H_
#define _GOLBAL_H_

#ifdef WIN32
#pragma warning ( disable : 4251 ) // suppress warnings about DLLS
#endif 

// switch boost::shared_ptr or tr1::shared_ptr
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
using boost::shared_ptr;
using boost::weak_ptr;

#endif