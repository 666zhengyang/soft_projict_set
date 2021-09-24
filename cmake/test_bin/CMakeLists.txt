#add_subdirectory(iot_server iot_server)
include (./cross.cmake)

#add_subdirectory(ipc)
set(TEST_BIN_SRC_FILES
test_bin.cpp
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../framework/out
)

LINK_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}/../framework/out
    )

add_definitions()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++11")

add_executable(test_bin ${TEST_BIN_SRC_FILES})

target_include_directories(test_bin
PRIVATE src)

install(TARGETS test_bin DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/out)
