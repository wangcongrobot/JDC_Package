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
include serial_JRC/tests/CMakeFiles/serial_JRC-test-timer.dir/depend.make

# Include the progress variables for this target.
include serial_JRC/tests/CMakeFiles/serial_JRC-test-timer.dir/progress.make

# Include the compile flags for this target's objects.
include serial_JRC/tests/CMakeFiles/serial_JRC-test-timer.dir/flags.make

serial_JRC/tests/CMakeFiles/serial_JRC-test-timer.dir/unit/unix_timer_tests.cc.o: serial_JRC/tests/CMakeFiles/serial_JRC-test-timer.dir/flags.make
serial_JRC/tests/CMakeFiles/serial_JRC-test-timer.dir/unit/unix_timer_tests.cc.o: /home/robot/catkin_ws/src/serial_JRC/tests/unit/unix_timer_tests.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/robot/catkin_ws/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object serial_JRC/tests/CMakeFiles/serial_JRC-test-timer.dir/unit/unix_timer_tests.cc.o"
	cd /home/robot/catkin_ws/build/serial_JRC/tests && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/serial_JRC-test-timer.dir/unit/unix_timer_tests.cc.o -c /home/robot/catkin_ws/src/serial_JRC/tests/unit/unix_timer_tests.cc

serial_JRC/tests/CMakeFiles/serial_JRC-test-timer.dir/unit/unix_timer_tests.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/serial_JRC-test-timer.dir/unit/unix_timer_tests.cc.i"
	cd /home/robot/catkin_ws/build/serial_JRC/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/robot/catkin_ws/src/serial_JRC/tests/unit/unix_timer_tests.cc > CMakeFiles/serial_JRC-test-timer.dir/unit/unix_timer_tests.cc.i

serial_JRC/tests/CMakeFiles/serial_JRC-test-timer.dir/unit/unix_timer_tests.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/serial_JRC-test-timer.dir/unit/unix_timer_tests.cc.s"
	cd /home/robot/catkin_ws/build/serial_JRC/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/robot/catkin_ws/src/serial_JRC/tests/unit/unix_timer_tests.cc -o CMakeFiles/serial_JRC-test-timer.dir/unit/unix_timer_tests.cc.s

serial_JRC/tests/CMakeFiles/serial_JRC-test-timer.dir/unit/unix_timer_tests.cc.o.requires:
.PHONY : serial_JRC/tests/CMakeFiles/serial_JRC-test-timer.dir/unit/unix_timer_tests.cc.o.requires

serial_JRC/tests/CMakeFiles/serial_JRC-test-timer.dir/unit/unix_timer_tests.cc.o.provides: serial_JRC/tests/CMakeFiles/serial_JRC-test-timer.dir/unit/unix_timer_tests.cc.o.requires
	$(MAKE) -f serial_JRC/tests/CMakeFiles/serial_JRC-test-timer.dir/build.make serial_JRC/tests/CMakeFiles/serial_JRC-test-timer.dir/unit/unix_timer_tests.cc.o.provides.build
.PHONY : serial_JRC/tests/CMakeFiles/serial_JRC-test-timer.dir/unit/unix_timer_tests.cc.o.provides

serial_JRC/tests/CMakeFiles/serial_JRC-test-timer.dir/unit/unix_timer_tests.cc.o.provides.build: serial_JRC/tests/CMakeFiles/serial_JRC-test-timer.dir/unit/unix_timer_tests.cc.o

# Object files for target serial_JRC-test-timer
serial_JRC__test__timer_OBJECTS = \
"CMakeFiles/serial_JRC-test-timer.dir/unit/unix_timer_tests.cc.o"

# External object files for target serial_JRC-test-timer
serial_JRC__test__timer_EXTERNAL_OBJECTS =

/home/robot/catkin_ws/devel/lib/serial_JRC/serial_JRC-test-timer: serial_JRC/tests/CMakeFiles/serial_JRC-test-timer.dir/unit/unix_timer_tests.cc.o
/home/robot/catkin_ws/devel/lib/serial_JRC/serial_JRC-test-timer: serial_JRC/tests/CMakeFiles/serial_JRC-test-timer.dir/build.make
/home/robot/catkin_ws/devel/lib/serial_JRC/serial_JRC-test-timer: gtest/libgtest.so
/home/robot/catkin_ws/devel/lib/serial_JRC/serial_JRC-test-timer: /home/robot/catkin_ws/devel/lib/libserial_JRC.so
/home/robot/catkin_ws/devel/lib/serial_JRC/serial_JRC-test-timer: serial_JRC/tests/CMakeFiles/serial_JRC-test-timer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable /home/robot/catkin_ws/devel/lib/serial_JRC/serial_JRC-test-timer"
	cd /home/robot/catkin_ws/build/serial_JRC/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/serial_JRC-test-timer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
serial_JRC/tests/CMakeFiles/serial_JRC-test-timer.dir/build: /home/robot/catkin_ws/devel/lib/serial_JRC/serial_JRC-test-timer
.PHONY : serial_JRC/tests/CMakeFiles/serial_JRC-test-timer.dir/build

serial_JRC/tests/CMakeFiles/serial_JRC-test-timer.dir/requires: serial_JRC/tests/CMakeFiles/serial_JRC-test-timer.dir/unit/unix_timer_tests.cc.o.requires
.PHONY : serial_JRC/tests/CMakeFiles/serial_JRC-test-timer.dir/requires

serial_JRC/tests/CMakeFiles/serial_JRC-test-timer.dir/clean:
	cd /home/robot/catkin_ws/build/serial_JRC/tests && $(CMAKE_COMMAND) -P CMakeFiles/serial_JRC-test-timer.dir/cmake_clean.cmake
.PHONY : serial_JRC/tests/CMakeFiles/serial_JRC-test-timer.dir/clean

serial_JRC/tests/CMakeFiles/serial_JRC-test-timer.dir/depend:
	cd /home/robot/catkin_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/robot/catkin_ws/src /home/robot/catkin_ws/src/serial_JRC/tests /home/robot/catkin_ws/build /home/robot/catkin_ws/build/serial_JRC/tests /home/robot/catkin_ws/build/serial_JRC/tests/CMakeFiles/serial_JRC-test-timer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : serial_JRC/tests/CMakeFiles/serial_JRC-test-timer.dir/depend

