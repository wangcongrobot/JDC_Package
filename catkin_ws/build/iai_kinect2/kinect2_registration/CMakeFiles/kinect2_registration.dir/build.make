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
include iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/depend.make

# Include the progress variables for this target.
include iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/progress.make

# Include the compile flags for this target's objects.
include iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/flags.make

iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/kinect2_registration.cpp.o: iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/flags.make
iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/kinect2_registration.cpp.o: /home/robot/catkin_ws/src/iai_kinect2/kinect2_registration/src/kinect2_registration.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/robot/catkin_ws/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/kinect2_registration.cpp.o"
	cd /home/robot/catkin_ws/build/iai_kinect2/kinect2_registration && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/kinect2_registration.dir/src/kinect2_registration.cpp.o -c /home/robot/catkin_ws/src/iai_kinect2/kinect2_registration/src/kinect2_registration.cpp

iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/kinect2_registration.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kinect2_registration.dir/src/kinect2_registration.cpp.i"
	cd /home/robot/catkin_ws/build/iai_kinect2/kinect2_registration && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/robot/catkin_ws/src/iai_kinect2/kinect2_registration/src/kinect2_registration.cpp > CMakeFiles/kinect2_registration.dir/src/kinect2_registration.cpp.i

iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/kinect2_registration.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kinect2_registration.dir/src/kinect2_registration.cpp.s"
	cd /home/robot/catkin_ws/build/iai_kinect2/kinect2_registration && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/robot/catkin_ws/src/iai_kinect2/kinect2_registration/src/kinect2_registration.cpp -o CMakeFiles/kinect2_registration.dir/src/kinect2_registration.cpp.s

iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/kinect2_registration.cpp.o.requires:
.PHONY : iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/kinect2_registration.cpp.o.requires

iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/kinect2_registration.cpp.o.provides: iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/kinect2_registration.cpp.o.requires
	$(MAKE) -f iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/build.make iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/kinect2_registration.cpp.o.provides.build
.PHONY : iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/kinect2_registration.cpp.o.provides

iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/kinect2_registration.cpp.o.provides.build: iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/kinect2_registration.cpp.o

iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/depth_registration_cpu.cpp.o: iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/flags.make
iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/depth_registration_cpu.cpp.o: /home/robot/catkin_ws/src/iai_kinect2/kinect2_registration/src/depth_registration_cpu.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/robot/catkin_ws/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/depth_registration_cpu.cpp.o"
	cd /home/robot/catkin_ws/build/iai_kinect2/kinect2_registration && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/kinect2_registration.dir/src/depth_registration_cpu.cpp.o -c /home/robot/catkin_ws/src/iai_kinect2/kinect2_registration/src/depth_registration_cpu.cpp

iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/depth_registration_cpu.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kinect2_registration.dir/src/depth_registration_cpu.cpp.i"
	cd /home/robot/catkin_ws/build/iai_kinect2/kinect2_registration && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/robot/catkin_ws/src/iai_kinect2/kinect2_registration/src/depth_registration_cpu.cpp > CMakeFiles/kinect2_registration.dir/src/depth_registration_cpu.cpp.i

iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/depth_registration_cpu.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kinect2_registration.dir/src/depth_registration_cpu.cpp.s"
	cd /home/robot/catkin_ws/build/iai_kinect2/kinect2_registration && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/robot/catkin_ws/src/iai_kinect2/kinect2_registration/src/depth_registration_cpu.cpp -o CMakeFiles/kinect2_registration.dir/src/depth_registration_cpu.cpp.s

iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/depth_registration_cpu.cpp.o.requires:
.PHONY : iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/depth_registration_cpu.cpp.o.requires

iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/depth_registration_cpu.cpp.o.provides: iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/depth_registration_cpu.cpp.o.requires
	$(MAKE) -f iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/build.make iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/depth_registration_cpu.cpp.o.provides.build
.PHONY : iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/depth_registration_cpu.cpp.o.provides

iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/depth_registration_cpu.cpp.o.provides.build: iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/depth_registration_cpu.cpp.o

iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/depth_registration_opencl.cpp.o: iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/flags.make
iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/depth_registration_opencl.cpp.o: /home/robot/catkin_ws/src/iai_kinect2/kinect2_registration/src/depth_registration_opencl.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/robot/catkin_ws/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/depth_registration_opencl.cpp.o"
	cd /home/robot/catkin_ws/build/iai_kinect2/kinect2_registration && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/kinect2_registration.dir/src/depth_registration_opencl.cpp.o -c /home/robot/catkin_ws/src/iai_kinect2/kinect2_registration/src/depth_registration_opencl.cpp

iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/depth_registration_opencl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kinect2_registration.dir/src/depth_registration_opencl.cpp.i"
	cd /home/robot/catkin_ws/build/iai_kinect2/kinect2_registration && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/robot/catkin_ws/src/iai_kinect2/kinect2_registration/src/depth_registration_opencl.cpp > CMakeFiles/kinect2_registration.dir/src/depth_registration_opencl.cpp.i

iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/depth_registration_opencl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kinect2_registration.dir/src/depth_registration_opencl.cpp.s"
	cd /home/robot/catkin_ws/build/iai_kinect2/kinect2_registration && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/robot/catkin_ws/src/iai_kinect2/kinect2_registration/src/depth_registration_opencl.cpp -o CMakeFiles/kinect2_registration.dir/src/depth_registration_opencl.cpp.s

iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/depth_registration_opencl.cpp.o.requires:
.PHONY : iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/depth_registration_opencl.cpp.o.requires

iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/depth_registration_opencl.cpp.o.provides: iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/depth_registration_opencl.cpp.o.requires
	$(MAKE) -f iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/build.make iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/depth_registration_opencl.cpp.o.provides.build
.PHONY : iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/depth_registration_opencl.cpp.o.provides

iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/depth_registration_opencl.cpp.o.provides.build: iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/depth_registration_opencl.cpp.o

# Object files for target kinect2_registration
kinect2_registration_OBJECTS = \
"CMakeFiles/kinect2_registration.dir/src/kinect2_registration.cpp.o" \
"CMakeFiles/kinect2_registration.dir/src/depth_registration_cpu.cpp.o" \
"CMakeFiles/kinect2_registration.dir/src/depth_registration_opencl.cpp.o"

# External object files for target kinect2_registration
kinect2_registration_EXTERNAL_OBJECTS =

/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/kinect2_registration.cpp.o
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/depth_registration_cpu.cpp.o
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/depth_registration_opencl.cpp.o
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/build.make
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /opt/ros/indigo/lib/libroscpp.so
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /usr/lib/x86_64-linux-gnu/libboost_signals.so
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /opt/ros/indigo/lib/librosconsole.so
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /opt/ros/indigo/lib/librosconsole_log4cxx.so
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /opt/ros/indigo/lib/librosconsole_backend_interface.so
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /usr/lib/liblog4cxx.so
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /usr/lib/x86_64-linux-gnu/libboost_regex.so
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /opt/ros/indigo/lib/libroscpp_serialization.so
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /opt/ros/indigo/lib/librostime.so
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /opt/ros/indigo/lib/libxmlrpcpp.so
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /opt/ros/indigo/lib/libcpp_common.so
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /usr/lib/x86_64-linux-gnu/libboost_system.so
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /usr/lib/x86_64-linux-gnu/libboost_thread.so
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /usr/lib/x86_64-linux-gnu/libpthread.so
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /usr/lib/x86_64-linux-gnu/libconsole_bridge.so
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /usr/lib/x86_64-linux-gnu/libopencv_videostab.so.2.4.8
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /usr/lib/x86_64-linux-gnu/libopencv_video.so.2.4.8
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /usr/lib/x86_64-linux-gnu/libopencv_superres.so.2.4.8
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /usr/lib/x86_64-linux-gnu/libopencv_stitching.so.2.4.8
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.2.4.8
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /usr/lib/x86_64-linux-gnu/libopencv_ocl.so.2.4.8
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.2.4.8
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.2.4.8
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /usr/lib/x86_64-linux-gnu/libopencv_legacy.so.2.4.8
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.2.4.8
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.2.4.8
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /usr/lib/x86_64-linux-gnu/libopencv_gpu.so.2.4.8
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.2.4.8
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.2.4.8
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /usr/lib/x86_64-linux-gnu/libopencv_core.so.2.4.8
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /usr/lib/x86_64-linux-gnu/libopencv_contrib.so.2.4.8
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.2.4.8
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /usr/lib/x86_64-linux-gnu/libOpenCL.so
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.2.4.8
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /usr/lib/x86_64-linux-gnu/libopencv_legacy.so.2.4.8
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /usr/lib/x86_64-linux-gnu/libopencv_video.so.2.4.8
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.2.4.8
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.2.4.8
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.2.4.8
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.2.4.8
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.2.4.8
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.2.4.8
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.2.4.8
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: /usr/lib/x86_64-linux-gnu/libopencv_core.so.2.4.8
/home/robot/catkin_ws/devel/lib/libkinect2_registration.so: iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library /home/robot/catkin_ws/devel/lib/libkinect2_registration.so"
	cd /home/robot/catkin_ws/build/iai_kinect2/kinect2_registration && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/kinect2_registration.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/build: /home/robot/catkin_ws/devel/lib/libkinect2_registration.so
.PHONY : iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/build

iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/requires: iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/kinect2_registration.cpp.o.requires
iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/requires: iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/depth_registration_cpu.cpp.o.requires
iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/requires: iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/src/depth_registration_opencl.cpp.o.requires
.PHONY : iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/requires

iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/clean:
	cd /home/robot/catkin_ws/build/iai_kinect2/kinect2_registration && $(CMAKE_COMMAND) -P CMakeFiles/kinect2_registration.dir/cmake_clean.cmake
.PHONY : iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/clean

iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/depend:
	cd /home/robot/catkin_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/robot/catkin_ws/src /home/robot/catkin_ws/src/iai_kinect2/kinect2_registration /home/robot/catkin_ws/build /home/robot/catkin_ws/build/iai_kinect2/kinect2_registration /home/robot/catkin_ws/build/iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : iai_kinect2/kinect2_registration/CMakeFiles/kinect2_registration.dir/depend

