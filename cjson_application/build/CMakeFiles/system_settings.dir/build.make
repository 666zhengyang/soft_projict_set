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
CMAKE_SOURCE_DIR = /home/zhengyang/work/zhengyang/soft_projict_set/cjson_application

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zhengyang/work/zhengyang/soft_projict_set/cjson_application/build

# Include any dependencies generated for this target.
include CMakeFiles/system_settings.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/system_settings.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/system_settings.dir/flags.make

CMakeFiles/system_settings.dir/src/cjson_application.cpp.o: CMakeFiles/system_settings.dir/flags.make
CMakeFiles/system_settings.dir/src/cjson_application.cpp.o: ../src/cjson_application.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhengyang/work/zhengyang/soft_projict_set/cjson_application/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/system_settings.dir/src/cjson_application.cpp.o"
	/home/zhengyang/work/git_server_work/tools/toolchain/bin/arm-openwrt-linux-gnueabi-g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/system_settings.dir/src/cjson_application.cpp.o -c /home/zhengyang/work/zhengyang/soft_projict_set/cjson_application/src/cjson_application.cpp

CMakeFiles/system_settings.dir/src/cjson_application.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/system_settings.dir/src/cjson_application.cpp.i"
	/home/zhengyang/work/git_server_work/tools/toolchain/bin/arm-openwrt-linux-gnueabi-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhengyang/work/zhengyang/soft_projict_set/cjson_application/src/cjson_application.cpp > CMakeFiles/system_settings.dir/src/cjson_application.cpp.i

CMakeFiles/system_settings.dir/src/cjson_application.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/system_settings.dir/src/cjson_application.cpp.s"
	/home/zhengyang/work/git_server_work/tools/toolchain/bin/arm-openwrt-linux-gnueabi-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhengyang/work/zhengyang/soft_projict_set/cjson_application/src/cjson_application.cpp -o CMakeFiles/system_settings.dir/src/cjson_application.cpp.s

CMakeFiles/system_settings.dir/src/cjson_application.cpp.o.requires:

.PHONY : CMakeFiles/system_settings.dir/src/cjson_application.cpp.o.requires

CMakeFiles/system_settings.dir/src/cjson_application.cpp.o.provides: CMakeFiles/system_settings.dir/src/cjson_application.cpp.o.requires
	$(MAKE) -f CMakeFiles/system_settings.dir/build.make CMakeFiles/system_settings.dir/src/cjson_application.cpp.o.provides.build
.PHONY : CMakeFiles/system_settings.dir/src/cjson_application.cpp.o.provides

CMakeFiles/system_settings.dir/src/cjson_application.cpp.o.provides.build: CMakeFiles/system_settings.dir/src/cjson_application.cpp.o


CMakeFiles/system_settings.dir/test.cpp.o: CMakeFiles/system_settings.dir/flags.make
CMakeFiles/system_settings.dir/test.cpp.o: ../test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhengyang/work/zhengyang/soft_projict_set/cjson_application/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/system_settings.dir/test.cpp.o"
	/home/zhengyang/work/git_server_work/tools/toolchain/bin/arm-openwrt-linux-gnueabi-g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/system_settings.dir/test.cpp.o -c /home/zhengyang/work/zhengyang/soft_projict_set/cjson_application/test.cpp

CMakeFiles/system_settings.dir/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/system_settings.dir/test.cpp.i"
	/home/zhengyang/work/git_server_work/tools/toolchain/bin/arm-openwrt-linux-gnueabi-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhengyang/work/zhengyang/soft_projict_set/cjson_application/test.cpp > CMakeFiles/system_settings.dir/test.cpp.i

CMakeFiles/system_settings.dir/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/system_settings.dir/test.cpp.s"
	/home/zhengyang/work/git_server_work/tools/toolchain/bin/arm-openwrt-linux-gnueabi-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhengyang/work/zhengyang/soft_projict_set/cjson_application/test.cpp -o CMakeFiles/system_settings.dir/test.cpp.s

CMakeFiles/system_settings.dir/test.cpp.o.requires:

.PHONY : CMakeFiles/system_settings.dir/test.cpp.o.requires

CMakeFiles/system_settings.dir/test.cpp.o.provides: CMakeFiles/system_settings.dir/test.cpp.o.requires
	$(MAKE) -f CMakeFiles/system_settings.dir/build.make CMakeFiles/system_settings.dir/test.cpp.o.provides.build
.PHONY : CMakeFiles/system_settings.dir/test.cpp.o.provides

CMakeFiles/system_settings.dir/test.cpp.o.provides.build: CMakeFiles/system_settings.dir/test.cpp.o


# Object files for target system_settings
system_settings_OBJECTS = \
"CMakeFiles/system_settings.dir/src/cjson_application.cpp.o" \
"CMakeFiles/system_settings.dir/test.cpp.o"

# External object files for target system_settings
system_settings_EXTERNAL_OBJECTS =

system_settings: CMakeFiles/system_settings.dir/src/cjson_application.cpp.o
system_settings: CMakeFiles/system_settings.dir/test.cpp.o
system_settings: CMakeFiles/system_settings.dir/build.make
system_settings: CMakeFiles/system_settings.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zhengyang/work/zhengyang/soft_projict_set/cjson_application/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable system_settings"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/system_settings.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/system_settings.dir/build: system_settings

.PHONY : CMakeFiles/system_settings.dir/build

CMakeFiles/system_settings.dir/requires: CMakeFiles/system_settings.dir/src/cjson_application.cpp.o.requires
CMakeFiles/system_settings.dir/requires: CMakeFiles/system_settings.dir/test.cpp.o.requires

.PHONY : CMakeFiles/system_settings.dir/requires

CMakeFiles/system_settings.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/system_settings.dir/cmake_clean.cmake
.PHONY : CMakeFiles/system_settings.dir/clean

CMakeFiles/system_settings.dir/depend:
	cd /home/zhengyang/work/zhengyang/soft_projict_set/cjson_application/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zhengyang/work/zhengyang/soft_projict_set/cjson_application /home/zhengyang/work/zhengyang/soft_projict_set/cjson_application /home/zhengyang/work/zhengyang/soft_projict_set/cjson_application/build /home/zhengyang/work/zhengyang/soft_projict_set/cjson_application/build /home/zhengyang/work/zhengyang/soft_projict_set/cjson_application/build/CMakeFiles/system_settings.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/system_settings.dir/depend

