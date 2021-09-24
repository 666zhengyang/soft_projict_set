project(INI_PARSER)
cmake_minimum_required(VERSION 2.8.12)
include (../../cross.cmake)

set (INI_PARSER_SRC_FILES
    ini_parser.cpp
)

include_directories (
    ${CMAKE_CURRENT_SOURCE_DIR}/../../framework/out
)

add_definitions()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -std=c++11")
add_library(ini_parser SHARED ${INI_PARSER_SRC_FILES})

set(INSTALL_HEAD_FILES src/ini_parser.h)

install(TARGETS ini_parser DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/out)
install(FILES ${INSTALL_HEAD_FILES} DESTINATION  ${CMAKE_CURRENT_SOURCE_DIR}/out/ini_parser)
