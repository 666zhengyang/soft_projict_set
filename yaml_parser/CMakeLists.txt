if(POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
endif(POLICY CMP0048)

project(YAML_TEST VERSION 0.0.1)
cmake_minimum_required(VERSION 2.8.12)
include (./cross.cmake)

# version

set(YAML_TEST_SRC_FILES
    test.cpp
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/yaml-cpp ${CMAKE_CURRENT_SOURCE_DIR}/yaml-cpp/yaml-cpp

)

LINK_DIRECTORIES(lib)

add_definitions()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++11")

add_executable(yaml_test ${YAML_TEST_SRC_FILES})

target_link_libraries(yaml_test 
	yaml-cpp)

target_include_directories(yaml_test
    PRIVATE yaml-cpp)

install(TARGETS yaml_test DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/./out)
