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
include object_recognition_ros/src/info_service/CMakeFiles/object_information_server.dir/depend.make

# Include the progress variables for this target.
include object_recognition_ros/src/info_service/CMakeFiles/object_information_server.dir/progress.make

# Include the compile flags for this target's objects.
include object_recognition_ros/src/info_service/CMakeFiles/object_information_server.dir/flags.make

object_recognition_ros/src/info_service/CMakeFiles/object_information_server.dir/info_service.cpp.o: object_recognition_ros/src/info_service/CMakeFiles/object_information_server.dir/flags.make
object_recognition_ros/src/info_service/CMakeFiles/object_information_server.dir/info_service.cpp.o: /home/robot/catkin_ws/src/object_recognition_ros/src/info_service/info_service.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/robot/catkin_ws/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object object_recognition_ros/src/info_service/CMakeFiles/object_information_server.dir/info_service.cpp.o"
	cd /home/robot/catkin_ws/build/object_recognition_ros/src/info_service && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/object_information_server.dir/info_service.cpp.o -c /home/robot/catkin_ws/src/object_recognition_ros/src/info_service/info_service.cpp

object_recognition_ros/src/info_service/CMakeFiles/object_information_server.dir/info_service.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/object_information_server.dir/info_service.cpp.i"
	cd /home/robot/catkin_ws/build/object_recognition_ros/src/info_service && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/robot/catkin_ws/src/object_recognition_ros/src/info_service/info_service.cpp > CMakeFiles/object_information_server.dir/info_service.cpp.i

object_recognition_ros/src/info_service/CMakeFiles/object_information_server.dir/info_service.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/object_information_server.dir/info_service.cpp.s"
	cd /home/robot/catkin_ws/build/object_recognition_ros/src/info_service && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/robot/catkin_ws/src/object_recognition_ros/src/info_service/info_service.cpp -o CMakeFiles/object_information_server.dir/info_service.cpp.s

object_recognition_ros/src/info_service/CMakeFiles/object_information_server.dir/info_service.cpp.o.requires:
.PHONY : object_recognition_ros/src/info_service/CMakeFiles/object_information_server.dir/info_service.cpp.o.requires

object_recognition_ros/src/info_service/CMakeFiles/object_information_server.dir/info_service.cpp.o.provides: object_recognition_ros/src/info_service/CMakeFiles/object_information_server.dir/info_service.cpp.o.requires
	$(MAKE) -f object_recognition_ros/src/info_service/CMakeFiles/object_information_server.dir/build.make object_recognition_ros/src/info_service/CMakeFiles/object_information_server.dir/info_service.cpp.o.provides.build
.PHONY : object_recognition_ros/src/info_service/CMakeFiles/object_information_server.dir/info_service.cpp.o.provides

object_recognition_ros/src/info_service/CMakeFiles/object_information_server.dir/info_service.cpp.o.provides.build: object_recognition_ros/src/info_service/CMakeFiles/object_information_server.dir/info_service.cpp.o

# Object files for target object_information_server
object_information_server_OBJECTS = \
"CMakeFiles/object_information_server.dir/info_service.cpp.o"

# External object files for target object_information_server
object_information_server_EXTERNAL_OBJECTS =

/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: object_recognition_ros/src/info_service/CMakeFiles/object_information_server.dir/info_service.cpp.o
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: object_recognition_ros/src/info_service/CMakeFiles/object_information_server.dir/build.make
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /opt/ros/indigo/lib/libgeometric_shapes.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /opt/ros/indigo/lib/liboctomap.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /opt/ros/indigo/lib/liboctomath.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /opt/ros/indigo/lib/librandom_numbers.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /home/robot/catkin_ws/devel/lib/libobject_recognition_core_db.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /home/robot/catkin_ws/devel/lib/libobject_recognition_core_common.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /opt/ros/indigo/lib/libecto.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /opt/ros/indigo/lib/libclass_loader.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/libPocoFoundation.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libdl.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /opt/ros/indigo/lib/libroslib.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /opt/ros/indigo/lib/librospack.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libpython2.7.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libtinyxml.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /opt/ros/indigo/lib/librosbag.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /opt/ros/indigo/lib/librosbag_storage.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libboost_program_options.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /opt/ros/indigo/lib/libroslz4.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/liblz4.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /opt/ros/indigo/lib/libtopic_tools.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /opt/ros/indigo/lib/libroscpp.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libboost_signals.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /opt/ros/indigo/lib/librosconsole.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /opt/ros/indigo/lib/librosconsole_log4cxx.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /opt/ros/indigo/lib/librosconsole_backend_interface.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/liblog4cxx.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libboost_regex.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /opt/ros/indigo/lib/libxmlrpcpp.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /opt/ros/indigo/lib/libroscpp_serialization.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /opt/ros/indigo/lib/librostime.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /opt/ros/indigo/lib/libcpp_common.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libboost_system.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libboost_thread.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libpthread.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libconsole_bridge.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /home/robot/catkin_ws/devel/lib/libobject_information_cache.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /opt/ros/indigo/lib/libgeometric_shapes.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /opt/ros/indigo/lib/liboctomap.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /opt/ros/indigo/lib/liboctomath.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /opt/ros/indigo/lib/librandom_numbers.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /home/robot/catkin_ws/devel/lib/libobject_recognition_core_common.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /home/robot/catkin_ws/devel/lib/libobject_recognition_core_db.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libboost_serialization.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libcurl.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libopencv_videostab.so.2.4.8
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libopencv_superres.so.2.4.8
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libopencv_stitching.so.2.4.8
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libopencv_ocl.so.2.4.8
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libopencv_gpu.so.2.4.8
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.2.4.8
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libopencv_legacy.so.2.4.8
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libopencv_contrib.so.2.4.8
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libopencv_video.so.2.4.8
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.2.4.8
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.2.4.8
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.2.4.8
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.2.4.8
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.2.4.8
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.2.4.8
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.2.4.8
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libopencv_core.so.2.4.8
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /opt/ros/indigo/lib/libecto.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /opt/ros/indigo/lib/libclass_loader.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/libPocoFoundation.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libdl.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /opt/ros/indigo/lib/libroslib.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /opt/ros/indigo/lib/librospack.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libpython2.7.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libtinyxml.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /opt/ros/indigo/lib/librosbag.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /opt/ros/indigo/lib/librosbag_storage.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libboost_program_options.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /opt/ros/indigo/lib/libroslz4.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/liblz4.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /opt/ros/indigo/lib/libtopic_tools.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /opt/ros/indigo/lib/libroscpp.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libboost_signals.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /opt/ros/indigo/lib/librosconsole.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /opt/ros/indigo/lib/librosconsole_log4cxx.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /opt/ros/indigo/lib/librosconsole_backend_interface.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/liblog4cxx.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libboost_regex.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /opt/ros/indigo/lib/libxmlrpcpp.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /opt/ros/indigo/lib/libroscpp_serialization.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /opt/ros/indigo/lib/librostime.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /opt/ros/indigo/lib/libcpp_common.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libboost_system.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libboost_thread.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libpthread.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: /usr/lib/x86_64-linux-gnu/libconsole_bridge.so
/home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server: object_recognition_ros/src/info_service/CMakeFiles/object_information_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable /home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server"
	cd /home/robot/catkin_ws/build/object_recognition_ros/src/info_service && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/object_information_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
object_recognition_ros/src/info_service/CMakeFiles/object_information_server.dir/build: /home/robot/catkin_ws/devel/lib/object_recognition_ros/object_information_server
.PHONY : object_recognition_ros/src/info_service/CMakeFiles/object_information_server.dir/build

object_recognition_ros/src/info_service/CMakeFiles/object_information_server.dir/requires: object_recognition_ros/src/info_service/CMakeFiles/object_information_server.dir/info_service.cpp.o.requires
.PHONY : object_recognition_ros/src/info_service/CMakeFiles/object_information_server.dir/requires

object_recognition_ros/src/info_service/CMakeFiles/object_information_server.dir/clean:
	cd /home/robot/catkin_ws/build/object_recognition_ros/src/info_service && $(CMAKE_COMMAND) -P CMakeFiles/object_information_server.dir/cmake_clean.cmake
.PHONY : object_recognition_ros/src/info_service/CMakeFiles/object_information_server.dir/clean

object_recognition_ros/src/info_service/CMakeFiles/object_information_server.dir/depend:
	cd /home/robot/catkin_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/robot/catkin_ws/src /home/robot/catkin_ws/src/object_recognition_ros/src/info_service /home/robot/catkin_ws/build /home/robot/catkin_ws/build/object_recognition_ros/src/info_service /home/robot/catkin_ws/build/object_recognition_ros/src/info_service/CMakeFiles/object_information_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : object_recognition_ros/src/info_service/CMakeFiles/object_information_server.dir/depend
