if(POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
endif(POLICY CMP0048)

project(BRAIN_HUB VERSION 0.0.1)
cmake_minimum_required(VERSION 2.8.12)
include (./cross.cmake)

# version
execute_process(
  COMMAND git log -1 --pretty=format:%h
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  OUTPUT_VARIABLE BRAIN_HUB_GIT_VERSION
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
string(TIMESTAMP TSTAMP "%Y%m%d")
string(APPEND BRAIN_HUB_FINAL_VERSION "V${BRAIN_HUB_VERSION}_${TSTAMP}_${BRAIN_HUB_GIT_VERSION}")
add_definitions(-DCURRENT_VERSION=${BRAIN_HUB_FINAL_VERSION})

set(AUDIO_TEST_SRC_FILES
    test.cpp
    audio/TinyPlay.cpp
    audio/TinyMix.cpp
    audio/AudioService.cpp
    audio/Tinymp3Play.cpp
)

include_directories(
    /home/zhengyang/work/git_server_work/framework/out  /home/zhengyang/work/git_server_work/framework/external_party/out
    ${CMAKE_CURRENT_SOURCE_DIR}/audio/tinymp3/include
)

LINK_DIRECTORIES(/home/zhengyang/work/git_server_work/framework/out  /home/zhengyang/work/git_server_work/framework/external_party/out
 ${CMAKE_CURRENT_SOURCE_DIR}/audio/tinymp3/lib)

add_definitions()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++11")

add_executable(audio_test ${AUDIO_TEST_SRC_FILES})

target_link_libraries(audio_test 
	adk pthread nanomsg protobuf tinyalsa tinymp3 mad asound yaml-cpp)

target_include_directories(audio_test
    PRIVATE src)

install(TARGETS audio_test DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/out)
