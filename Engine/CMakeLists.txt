INCLUDE_DIRECTORIES(${COMMON})
INCLUDE_DIRECTORIES(${PYTHON27})

SET(ENGINE_SRC
        Engine.h Engine.cpp
        BacktestTimeHandler.cpp BacktestTimeHandler.h
        Scheduler.cpp Scheduler.h
        )

ADD_LIBRARY(Engine SHARED ${ENGINE_SRC})
TARGET_LINK_LIBRARIES(Engine ${Boost_LIBRARIES} Data Algorithm)