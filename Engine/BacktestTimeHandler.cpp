#include "stdafx.h"
#include "BacktestTimeHandler.h"

BacktestTimeHandler::BacktestTimeHandler(const boost::posix_time::ptime & start_time, Resolution res)
   : m_current_time(start_time),
   m_res(res)
{
}

BacktestTimeHandler::~BacktestTimeHandler()
{
}

void BacktestTimeHandler::step()
{
   m_current_time += duration(m_res);
}

const boost::posix_time::ptime BacktestTimeHandler::get_current_time()
{ 
   return m_current_time; 
}