#include "StdAfx.h"
#include "Portfolio.h"
#include "Brokerage.h"
#include "AlgorithmManager.h"
#include "Algorithm.h"
#include "PortfolioManager.h"
#include "logger.h"
#include "../Data/DataSlice.h"

AlgorithmManager::AlgorithmManager(const shared_ptr<Brokerage>& brokerage, const shared_ptr<Algorithm>& algorithm, const shared_ptr<Portfolio>& portfolio)
   :m_brokerage(brokerage),
   m_portfolio(portfolio),
   m_algorithm(algorithm),
   m_active(false)
{
}

AlgorithmManager::~AlgorithmManager(void)
{
   //m_portfolio_manager->release();
}

void AlgorithmManager::init()
{
   m_portfolio_manager = shared_ptr<PortfolioManager>(new PortfolioManager());
   m_portfolio_manager->register_portfolio(m_portfolio);
   m_portfolio_manager->register_brokerage(m_brokerage);
   m_brokerage->register_call_back(m_portfolio_manager);
   m_algorithm->register_call_back(m_portfolio_manager);
}

void AlgorithmManager::run()
{
   if( !m_active )
   {
      init();
      m_active = true;
   }
   m_portfolio_manager->run();
}

void AlgorithmManager::do_cycle(const shared_ptr<DataSlice>& p_data)
{
   m_algorithm->on_data(p_data);

   portfoliolog << p_data->get_start_time() << "," << m_portfolio_manager->query_net_value(p_data);
}