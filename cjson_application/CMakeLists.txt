project(SYSTEM_SETTINGS)
cmake_minimum_required(VERSION 2.8.12)
include (./cross.cmake)

set(SYSTEM_SETTINGS_SRC_FILES
    src/cjson_application.cpp
    test.cpp
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/lib  ${CMAKE_CURRENT_SOURCE_DIR}/inc
    )

LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_definitions()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++11")

add_executable(system_settings ${SYSTEM_SETTINGS_SRC_FILES})

target_link_libraries(system_settings
   cjson)

target_include_directories(system_settings
    PRIVATE src)

install(TARGETS system_settings DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/./out)
