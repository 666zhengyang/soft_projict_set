if(POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
endif(POLICY CMP0048)

project(UART_TEST VERSION 0.0.1)
cmake_minimum_required(VERSION 2.8.12)
include (./cross.cmake)

# version

set(UART_TEST_SRC_FILES
    src/test.cpp
    src/uart.cpp
    src/chassis_port.cpp
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/inc

)

LINK_DIRECTORIES(lib)

add_definitions()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++11")

add_executable(uart_test ${UART_TEST_SRC_FILES})

target_link_libraries(uart_test 
	pthread)

target_include_directories(uart_test
    PRIVATE yaml-cpp)

install(TARGETS uart_test DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/./out)
