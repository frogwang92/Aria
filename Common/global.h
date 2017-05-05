#ifndef _GLOBAL_H_
#define _GOLBAL_H_

#ifdef WIN32
#pragma warning ( disable : 4251 ) // suppress warnings about DLLS
#endif

#include <memory>

using std::shared_ptr;
using std::weak_ptr;

#endif