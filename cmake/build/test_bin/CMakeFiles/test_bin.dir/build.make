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
include test_bin/CMakeFiles/test_bin.dir/depend.make

# Include the progress variables for this target.
include test_bin/CMakeFiles/test_bin.dir/progress.make

# Include the compile flags for this target's objects.
include test_bin/CMakeFiles/test_bin.dir/flags.make

test_bin/CMakeFiles/test_bin.dir/test_bin.cpp.o: test_bin/CMakeFiles/test_bin.dir/flags.make
test_bin/CMakeFiles/test_bin.dir/test_bin.cpp.o: ../test_bin/test_bin.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhengyang/work/zhengyang/soft_projict_set/cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test_bin/CMakeFiles/test_bin.dir/test_bin.cpp.o"
	cd /home/zhengyang/work/zhengyang/soft_projict_set/cmake/build/test_bin && /opt/toolchain/bin/arm-openwrt-linux-gnueabi-g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_bin.dir/test_bin.cpp.o -c /home/zhengyang/work/zhengyang/soft_projict_set/cmake/test_bin/test_bin.cpp

test_bin/CMakeFiles/test_bin.dir/test_bin.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_bin.dir/test_bin.cpp.i"
	cd /home/zhengyang/work/zhengyang/soft_projict_set/cmake/build/test_bin && /opt/toolchain/bin/arm-openwrt-linux-gnueabi-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhengyang/work/zhengyang/soft_projict_set/cmake/test_bin/test_bin.cpp > CMakeFiles/test_bin.dir/test_bin.cpp.i

test_bin/CMakeFiles/test_bin.dir/test_bin.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_bin.dir/test_bin.cpp.s"
	cd /home/zhengyang/work/zhengyang/soft_projict_set/cmake/build/test_bin && /opt/toolchain/bin/arm-openwrt-linux-gnueabi-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhengyang/work/zhengyang/soft_projict_set/cmake/test_bin/test_bin.cpp -o CMakeFiles/test_bin.dir/test_bin.cpp.s

test_bin/CMakeFiles/test_bin.dir/test_bin.cpp.o.requires:

.PHONY : test_bin/CMakeFiles/test_bin.dir/test_bin.cpp.o.requires

test_bin/CMakeFiles/test_bin.dir/test_bin.cpp.o.provides: test_bin/CMakeFiles/test_bin.dir/test_bin.cpp.o.requires
	$(MAKE) -f test_bin/CMakeFiles/test_bin.dir/build.make test_bin/CMakeFiles/test_bin.dir/test_bin.cpp.o.provides.build
.PHONY : test_bin/CMakeFiles/test_bin.dir/test_bin.cpp.o.provides

test_bin/CMakeFiles/test_bin.dir/test_bin.cpp.o.provides.build: test_bin/CMakeFiles/test_bin.dir/test_bin.cpp.o


# Object files for target test_bin
test_bin_OBJECTS = \
"CMakeFiles/test_bin.dir/test_bin.cpp.o"

# External object files for target test_bin
test_bin_EXTERNAL_OBJECTS =

test_bin/test_bin: test_bin/CMakeFiles/test_bin.dir/test_bin.cpp.o
test_bin/test_bin: test_bin/CMakeFiles/test_bin.dir/build.make
test_bin/test_bin: test_bin/CMakeFiles/test_bin.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zhengyang/work/zhengyang/soft_projict_set/cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_bin"
	cd /home/zhengyang/work/zhengyang/soft_projict_set/cmake/build/test_bin && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_bin.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test_bin/CMakeFiles/test_bin.dir/build: test_bin/test_bin

.PHONY : test_bin/CMakeFiles/test_bin.dir/build

test_bin/CMakeFiles/test_bin.dir/requires: test_bin/CMakeFiles/test_bin.dir/test_bin.cpp.o.requires

.PHONY : test_bin/CMakeFiles/test_bin.dir/requires

test_bin/CMakeFiles/test_bin.dir/clean:
	cd /home/zhengyang/work/zhengyang/soft_projict_set/cmake/build/test_bin && $(CMAKE_COMMAND) -P CMakeFiles/test_bin.dir/cmake_clean.cmake
.PHONY : test_bin/CMakeFiles/test_bin.dir/clean

test_bin/CMakeFiles/test_bin.dir/depend:
	cd /home/zhengyang/work/zhengyang/soft_projict_set/cmake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zhengyang/work/zhengyang/soft_projict_set/cmake /home/zhengyang/work/zhengyang/soft_projict_set/cmake/test_bin /home/zhengyang/work/zhengyang/soft_projict_set/cmake/build /home/zhengyang/work/zhengyang/soft_projict_set/cmake/build/test_bin /home/zhengyang/work/zhengyang/soft_projict_set/cmake/build/test_bin/CMakeFiles/test_bin.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test_bin/CMakeFiles/test_bin.dir/depend

