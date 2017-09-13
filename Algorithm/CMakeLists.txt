INCLUDE_DIRECTORIES(${COMMON})
INCLUDE_DIRECTORIES(${PYTHON27})

SET(ALGO_SRC
        Algorithm.cpp Algorithm.h
        BacktestBrokerage.cpp BacktestBrokerage.h
        Brokerage.cpp Brokerage.h
        Portfolio.cpp Portfolio.h
        PortfolioManager.cpp PortfolioManager.h
        TradeJobNode.cpp TradeJobNode.h
        Algo_turtle_intraday.cpp Algo_turtle_intraday.h)

ADD_LIBRARY(Algorithm SHARED ${ALGO_SRC})
TARGET_LINK_LIBRARIES(Algorithm ${Boost_LIBRARIES} Data)