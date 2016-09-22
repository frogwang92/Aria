#pragma once
#ifndef _OHLCV_H_
#define _OHLCV_H_

#include "Common.h"  

#ifdef DATA_EXPORTS  
#define DATA_CLASS DLL_EXPORT_CLASS_DECL  
#define DATA_API DLL_EXPORT_DECL  
#else  
#define DATA_CLASS DLL_IMPORT_CLASS_DECL  
#define DATA_API DLL_IMPORT_DECL  
#endif 

#include "stdafx.h"
#include "OHLC.h"

class DATA_CLASS OHLCV :
   public OHLC
{
public:
   OHLCV(void);
   OHLCV(int open, int close, int high, int low, int adj_close, int vol);
   OHLCV(int open, int close, int high, int low, int adj_close, const boost::posix_time::ptime& starttime, Resolution res, int vol);
   ~OHLCV(void);

public:
   int volume() const { return m_volume; }
   
private:
   int m_volume;
};

inline ostream & operator<<(ostream &stream, const OHLCV & right)
{
   stream << (OHLC)right << "," << right.volume();

   return stream;
}

#endif