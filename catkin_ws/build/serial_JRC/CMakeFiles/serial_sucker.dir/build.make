# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

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
CMAKE_SOURCE_DIR = /home/robot/catkin_ws/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/robot/catkin_ws/build

# Include any dependencies generated for this target.
include serial_JRC/CMakeFiles/serial_sucker.dir/depend.make

# Include the progress variables for this target.
include serial_JRC/CMakeFiles/serial_sucker.dir/progress.make

# Include the compile flags for this target's objects.
include serial_JRC/CMakeFiles/serial_sucker.dir/flags.make

serial_JRC/CMakeFiles/serial_sucker.dir/examples/serial_sucker.cc.o: serial_JRC/CMakeFiles/serial_sucker.dir/flags.make
serial_JRC/CMakeFiles/serial_sucker.dir/examples/serial_sucker.cc.o: /home/robot/catkin_ws/src/serial_JRC/examples/serial_sucker.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/robot/catkin_ws/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object serial_JRC/CMakeFiles/serial_sucker.dir/examples/serial_sucker.cc.o"
	cd /home/robot/catkin_ws/build/serial_JRC && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/serial_sucker.dir/examples/serial_sucker.cc.o -c /home/robot/catkin_ws/src/serial_JRC/examples/serial_sucker.cc

serial_JRC/CMakeFiles/serial_sucker.dir/examples/serial_sucker.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/serial_sucker.dir/examples/serial_sucker.cc.i"
	cd /home/robot/catkin_ws/build/serial_JRC && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/robot/catkin_ws/src/serial_JRC/examples/serial_sucker.cc > CMakeFiles/serial_sucker.dir/examples/serial_sucker.cc.i

serial_JRC/CMakeFiles/serial_sucker.dir/examples/serial_sucker.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/serial_sucker.dir/examples/serial_sucker.cc.s"
	cd /home/robot/catkin_ws/build/serial_JRC && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/robot/catkin_ws/src/serial_JRC/examples/serial_sucker.cc -o CMakeFiles/serial_sucker.dir/examples/serial_sucker.cc.s

serial_JRC/CMakeFiles/serial_sucker.dir/examples/serial_sucker.cc.o.requires:
.PHONY : serial_JRC/CMakeFiles/serial_sucker.dir/examples/serial_sucker.cc.o.requires

serial_JRC/CMakeFiles/serial_sucker.dir/examples/serial_sucker.cc.o.provides: serial_JRC/CMakeFiles/serial_sucker.dir/examples/serial_sucker.cc.o.requires
	$(MAKE) -f serial_JRC/CMakeFiles/serial_sucker.dir/build.make serial_JRC/CMakeFiles/serial_sucker.dir/examples/serial_sucker.cc.o.provides.build
.PHONY : serial_JRC/CMakeFiles/serial_sucker.dir/examples/serial_sucker.cc.o.provides

serial_JRC/CMakeFiles/serial_sucker.dir/examples/serial_sucker.cc.o.provides.build: serial_JRC/CMakeFiles/serial_sucker.dir/examples/serial_sucker.cc.o

# Object files for target serial_sucker
serial_sucker_OBJECTS = \
"CMakeFiles/serial_sucker.dir/examples/serial_sucker.cc.o"

# External object files for target serial_sucker
serial_sucker_EXTERNAL_OBJECTS =

/home/robot/catkin_ws/devel/lib/serial_JRC/serial_sucker: serial_JRC/CMakeFiles/serial_sucker.dir/examples/serial_sucker.cc.o
/home/robot/catkin_ws/devel/lib/serial_JRC/serial_sucker: serial_JRC/CMakeFiles/serial_sucker.dir/build.make
/home/robot/catkin_ws/devel/lib/serial_JRC/serial_sucker: /home/robot/catkin_ws/devel/lib/libserial_JRC.so
/home/robot/catkin_ws/devel/lib/serial_JRC/serial_sucker: /opt/ros/indigo/lib/libroscpp.so
/home/robot/catkin_ws/devel/lib/serial_JRC/serial_sucker: /usr/lib/x86_64-linux-gnu/libboost_signals.so
/home/robot/catkin_ws/devel/lib/serial_JRC/serial_sucker: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
/home/robot/catkin_ws/devel/lib/serial_JRC/serial_sucker: /opt/ros/indigo/lib/librosconsole.so
/home/robot/catkin_ws/devel/lib/serial_JRC/serial_sucker: /opt/ros/indigo/lib/librosconsole_log4cxx.so
/home/robot/catkin_ws/devel/lib/serial_JRC/serial_sucker: /opt/ros/indigo/lib/librosconsole_backend_interface.so
/home/robot/catkin_ws/devel/lib/serial_JRC/serial_sucker: /usr/lib/liblog4cxx.so
/home/robot/catkin_ws/devel/lib/serial_JRC/serial_sucker: /usr/lib/x86_64-linux-gnu/libboost_regex.so
/home/robot/catkin_ws/devel/lib/serial_JRC/serial_sucker: /opt/ros/indigo/lib/libxmlrpcpp.so
/home/robot/catkin_ws/devel/lib/serial_JRC/serial_sucker: /opt/ros/indigo/lib/libroscpp_serialization.so
/home/robot/catkin_ws/devel/lib/serial_JRC/serial_sucker: /opt/ros/indigo/lib/librostime.so
/home/robot/catkin_ws/devel/lib/serial_JRC/serial_sucker: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
/home/robot/catkin_ws/devel/lib/serial_JRC/serial_sucker: /opt/ros/indigo/lib/libcpp_common.so
/home/robot/catkin_ws/devel/lib/serial_JRC/serial_sucker: /usr/lib/x86_64-linux-gnu/libboost_system.so
/home/robot/catkin_ws/devel/lib/serial_JRC/serial_sucker: /usr/lib/x86_64-linux-gnu/libboost_thread.so
/home/robot/catkin_ws/devel/lib/serial_JRC/serial_sucker: /usr/lib/x86_64-linux-gnu/libpthread.so
/home/robot/catkin_ws/devel/lib/serial_JRC/serial_sucker: /usr/lib/x86_64-linux-gnu/libconsole_bridge.so
/home/robot/catkin_ws/devel/lib/serial_JRC/serial_sucker: serial_JRC/CMakeFiles/serial_sucker.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable /home/robot/catkin_ws/devel/lib/serial_JRC/serial_sucker"
	cd /home/robot/catkin_ws/build/serial_JRC && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/serial_sucker.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
serial_JRC/CMakeFiles/serial_sucker.dir/build: /home/robot/catkin_ws/devel/lib/serial_JRC/serial_sucker
.PHONY : serial_JRC/CMakeFiles/serial_sucker.dir/build

serial_JRC/CMakeFiles/serial_sucker.dir/requires: serial_JRC/CMakeFiles/serial_sucker.dir/examples/serial_sucker.cc.o.requires
.PHONY : serial_JRC/CMakeFiles/serial_sucker.dir/requires

serial_JRC/CMakeFiles/serial_sucker.dir/clean:
	cd /home/robot/catkin_ws/build/serial_JRC && $(CMAKE_COMMAND) -P CMakeFiles/serial_sucker.dir/cmake_clean.cmake
.PHONY : serial_JRC/CMakeFiles/serial_sucker.dir/clean

serial_JRC/CMakeFiles/serial_sucker.dir/depend:
	cd /home/robot/catkin_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/robot/catkin_ws/src /home/robot/catkin_ws/src/serial_JRC /home/robot/catkin_ws/build /home/robot/catkin_ws/build/serial_JRC /home/robot/catkin_ws/build/serial_JRC/CMakeFiles/serial_sucker.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : serial_JRC/CMakeFiles/serial_sucker.dir/depend

