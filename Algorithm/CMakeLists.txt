INCLUDE_DIRECTORIES(${COMMON})
INCLUDE_DIRECTORIES(${PYTHON27})

SET(ALGO_SRC
        IAlgorithmManager.h
        BoostExport.h
        Algorithm.cpp Algorithm.h
        Algorithm_Buyandhold.cpp Algorithm_Buyandhold.h
        Algorithm_Py.cpp Algorithm_Py.h
        AlgorithmInitializer.cpp AlgorithmInitializer.h
        AlgorithmManager.cpp AlgorithmManager.h
        BacktestBrokerage.cpp BacktestBrokerage.h
        Brokerage.cpp Brokerage.h
        Portfolio.cpp Portfolio.h
        PortfolioManager.cpp PortfolioManager.h
        TradeJobNode.cpp TradeJobNode.h
        )

ADD_LIBRARY(Algorithm SHARED ${ALGO_SRC})
TARGET_LINK_LIBRARIES(Algorithm ${Boost_LIBRARIES} Data)