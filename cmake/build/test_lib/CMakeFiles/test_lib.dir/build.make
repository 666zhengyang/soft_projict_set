# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zhengyang/work/zhengyang/soft_projict_set/cmake

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zhengyang/work/zhengyang/soft_projict_set/cmake/build

# Include any dependencies generated for this target.
include test_lib/CMakeFiles/test_lib.dir/depend.make

# Include the progress variables for this target.
include test_lib/CMakeFiles/test_lib.dir/progress.make

# Include the compile flags for this target's objects.
include test_lib/CMakeFiles/test_lib.dir/flags.make

test_lib/CMakeFiles/test_lib.dir/test_lib.cpp.o: test_lib/CMakeFiles/test_lib.dir/flags.make
test_lib/CMakeFiles/test_lib.dir/test_lib.cpp.o: ../test_lib/test_lib.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhengyang/work/zhengyang/soft_projict_set/cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test_lib/CMakeFiles/test_lib.dir/test_lib.cpp.o"
	cd /home/zhengyang/work/zhengyang/soft_projict_set/cmake/build/test_lib && /opt/toolchain/bin/arm-openwrt-linux-gnueabi-g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_lib.dir/test_lib.cpp.o -c /home/zhengyang/work/zhengyang/soft_projict_set/cmake/test_lib/test_lib.cpp

test_lib/CMakeFiles/test_lib.dir/test_lib.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_lib.dir/test_lib.cpp.i"
	cd /home/zhengyang/work/zhengyang/soft_projict_set/cmake/build/test_lib && /opt/toolchain/bin/arm-openwrt-linux-gnueabi-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhengyang/work/zhengyang/soft_projict_set/cmake/test_lib/test_lib.cpp > CMakeFiles/test_lib.dir/test_lib.cpp.i

test_lib/CMakeFiles/test_lib.dir/test_lib.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_lib.dir/test_lib.cpp.s"
	cd /home/zhengyang/work/zhengyang/soft_projict_set/cmake/build/test_lib && /opt/toolchain/bin/arm-openwrt-linux-gnueabi-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhengyang/work/zhengyang/soft_projict_set/cmake/test_lib/test_lib.cpp -o CMakeFiles/test_lib.dir/test_lib.cpp.s

test_lib/CMakeFiles/test_lib.dir/test_lib.cpp.o.requires:

.PHONY : test_lib/CMakeFiles/test_lib.dir/test_lib.cpp.o.requires

test_lib/CMakeFiles/test_lib.dir/test_lib.cpp.o.provides: test_lib/CMakeFiles/test_lib.dir/test_lib.cpp.o.requires
	$(MAKE) -f test_lib/CMakeFiles/test_lib.dir/build.make test_lib/CMakeFiles/test_lib.dir/test_lib.cpp.o.provides.build
.PHONY : test_lib/CMakeFiles/test_lib.dir/test_lib.cpp.o.provides

test_lib/CMakeFiles/test_lib.dir/test_lib.cpp.o.provides.build: test_lib/CMakeFiles/test_lib.dir/test_lib.cpp.o


# Object files for target test_lib
test_lib_OBJECTS = \
"CMakeFiles/test_lib.dir/test_lib.cpp.o"

# External object files for target test_lib
test_lib_EXTERNAL_OBJECTS =

test_lib/libtest_lib.so: test_lib/CMakeFiles/test_lib.dir/test_lib.cpp.o
test_lib/libtest_lib.so: test_lib/CMakeFiles/test_lib.dir/build.make
test_lib/libtest_lib.so: test_lib/CMakeFiles/test_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zhengyang/work/zhengyang/soft_projict_set/cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libtest_lib.so"
	cd /home/zhengyang/work/zhengyang/soft_projict_set/cmake/build/test_lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test_lib/CMakeFiles/test_lib.dir/build: test_lib/libtest_lib.so

.PHONY : test_lib/CMakeFiles/test_lib.dir/build

test_lib/CMakeFiles/test_lib.dir/requires: test_lib/CMakeFiles/test_lib.dir/test_lib.cpp.o.requires

.PHONY : test_lib/CMakeFiles/test_lib.dir/requires

test_lib/CMakeFiles/test_lib.dir/clean:
	cd /home/zhengyang/work/zhengyang/soft_projict_set/cmake/build/test_lib && $(CMAKE_COMMAND) -P CMakeFiles/test_lib.dir/cmake_clean.cmake
.PHONY : test_lib/CMakeFiles/test_lib.dir/clean

test_lib/CMakeFiles/test_lib.dir/depend:
	cd /home/zhengyang/work/zhengyang/soft_projict_set/cmake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zhengyang/work/zhengyang/soft_projict_set/cmake /home/zhengyang/work/zhengyang/soft_projict_set/cmake/test_lib /home/zhengyang/work/zhengyang/soft_projict_set/cmake/build /home/zhengyang/work/zhengyang/soft_projict_set/cmake/build/test_lib /home/zhengyang/work/zhengyang/soft_projict_set/cmake/build/test_lib/CMakeFiles/test_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test_lib/CMakeFiles/test_lib.dir/depend

