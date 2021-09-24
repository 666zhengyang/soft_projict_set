



include (./cross.cmake)

#add_subdirectory(ipc)
set(TEST_LIB_LIB_SRC_FILES
    test_lib.cpp
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../framework/out
)

LINK_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}/../framework/out
    )

add_definitions()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++11")

add_library(test_lib SHARED ${TEST_LIB_LIB_SRC_FILES})

target_link_libraries(test_lib 
    )

target_include_directories(test_lib
    PRIVATE src)

install(TARGETS test_lib DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/out)
