INCLUDE_DIRECTORIES(${COMMON})
INCLUDE_DIRECTORIES(${PYTHON27})

SET(ARIA_SRC
        Aria.cpp
        )

ADD_EXECUTABLE(${PROJECT_NAME} ${ARIA_SRC})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} ${LIBPYTHON})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${Boost_LIBRARIES} Engine)

SET(PYDATASRC ${PROJECT_SOURCE_DIR}/Aria/py_datasources)
SET(PYALGOS ${PROJECT_SOURCE_DIR}/Aria/py_algos)
SET(TARGETLOCATION ${PROJECT_BINARY_DIR}/Aria)

FILE(GLOB DataSrcs ${PYDATASRC}/*.*)

foreach (datasrc ${DataSrcs})
    add_custom_command(TARGET Aria POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E
            copy ${datasrc} $<TARGET_FILE_DIR:Aria>)
endforeach ()

FILE(GLOB Algos ${PYALGOS}/*.*)

foreach (algo ${Algos})
    add_custom_command(TARGET Aria POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E
            copy ${algo} $<TARGET_FILE_DIR:Aria>)
endforeach ()