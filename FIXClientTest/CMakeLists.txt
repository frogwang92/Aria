INCLUDE_DIRECTORIES(${COMMON})

SET(FIXCLIENTTEST_SRC
        FIXClientTest.cpp
        )

ADD_EXECUTABLE(FIXClientTest ${FIXCLIENTTEST_SRC})
TARGET_LINK_LIBRARIES(FIXClientTest ${QUICKFIX_LIB} FIXClient)