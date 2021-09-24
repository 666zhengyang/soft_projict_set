
if(POLICY CMP0048)
cmake_policy(SET CMP0048 NEW)
endif(POLICY CMP0048)

project(TEST VERSION 0.3.0)
cmake_minimum_required(VERSION 2.8.12)

add_subdirectory(test_lib)
add_subdirectory(test_bin)
set(TEST_SRC_FILES
    test.cpp
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../framework/out
)

LINK_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}/../framework/out
    )

add_definitions()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++11")

add_executable(test_otm ${TEST_SRC_FILES})

target_link_libraries(test_otm 
    )

target_include_directories(test_otm
    PRIVATE src)

install(TARGETS test_otm DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/out)
