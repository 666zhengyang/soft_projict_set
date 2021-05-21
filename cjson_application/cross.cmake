SET(CROSS_COMPILE 1)

IF(CROSS_COMPILE) 
  
SET(CMAKE_SYSTEM_NAME Linux)
SET(TOOLCHAIN_DIR "/home/zhengyang/work/zhengyang/crosstools/toolchain")

set(CMAKE_CXX_COMPILER ${TOOLCHAIN_DIR}/bin/arm-openwrt-linux-gnueabi-g++)
set(CMAKE_C_COMPILER   ${TOOLCHAIN_DIR}/bin/arm-openwrt-linux-gnueabi-gcc)
set(GNU_FLAGS "-Os -pipe -march=armv7-a -mtune=cortex-a7 -mfpu=neon -fno-caller-saves -Wno-unused-result -mfloat-abi=hard  -Wformat -Werror=format-security -D_FORTIFY_SOURCE=1 -Wl,-z,now -Wl,-z,relro   -DNDEBUG   -w -g")
set(CMAKE_CXX_FLAGS "${GNU_FLAGS}")
set(CMAKE_C_FLAGS "${GNU_FLAGS}")

SET(CMAKE_FIND_ROOT_PATH  ${TOOLCHAIN_DIR}
 ${TOOLCHAIN_DIR}/arm-none-linux-gnueabi/include
 ${TOOLCHAIN_DIR}/arm-none-linux-gnueabi/lib )

#ADD_DEFINITIONS(-DTEST_IPC)

ENDIF(CROSS_COMPILE)
