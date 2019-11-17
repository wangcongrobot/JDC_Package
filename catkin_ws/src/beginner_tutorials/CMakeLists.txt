cmake_minimum_required(VERSION 2.8.3)
project(beginner_tutorials)
set(CMAKE_CXX_FLAGS "-std=c++0x" )


## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
  id_data_msgs
)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)


## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

################################################
## Declare ROS messages, services and actions ##
################################################

## To declare and build messages, services or actions from within this
## package, follow these steps:
## * Let MSG_DEP_SET be the set of packages whose message types you use in
##   your messages/services/actions (e.g. std_msgs, actionlib_msgs, ...).
## * In the file package.xml:
##   * add a build_depend and a run_depend tag for each package in MSG_DEP_SET
##   * If MSG_DEP_SET isn't empty the following dependencies might have been
##     pulled in transitively but can be declared for certainty nonetheless:
##     * add a build_depend tag for "message_generation"
##     * add a run_depend tag for "message_runtime"
## * In this file (CMakeLists.txt):
##   * add "message_generation" and every package in MSG_DEP_SET to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * add "message_runtime" and every package in MSG_DEP_SET to
##     catkin_package(CATKIN_DEPENDS ...)
##   * uncomment the add_*_files sections below as needed
##     and list every .msg/.srv/.action file to be processed
##   * uncomment the generate_messages entry below
##   * add every package in MSG_DEP_SET to generate_messages(DEPENDENCIES ...)

## Generate messages in the 'msg' folder
 add_message_files(
   FILES
   Num.msg
   ForceData.msg
 )

## Generate services in the 'srv' folder
 add_service_files(
   FILES
   AddTwoInts.srv
 )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
 generate_messages(
   DEPENDENCIES
   std_msgs
 )

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES beginner_tutorials
#  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
  CATKIN_DEPENDS message_runtime
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
)

## Declare a cpp library
# add_library(beginner_tutorials
#   src/${PROJECT_NAME}/beginner_tutorials.cpp
# )

## Declare a cpp executable
# add_executable(beginner_tutorials_node src/beginner_tutorials_node.cpp)

## Add cmake target dependencies of the executable/library
## as an example, message headers may need to be generated before nodes
# add_dependencies(beginner_tutorials_node beginner_tutorials_generate_messages_cpp)

## Specify libraries to link a library or executable target against
# target_link_libraries(beginner_tutorials_node
#   ${catkin_LIBRARIES}
# )

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables and/or libraries for installation
# install(TARGETS beginner_tutorials beginner_tutorials_node
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_beginner_tutorials.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
#add_executable(circle_my_turtle src/circlemyturtle.cpp)
#target_link_libraries(circle_my_turtle ${catkin_LIBRARIES})


#add_executable(move_my_turtle src/move_my_turtle.cpp)
#target_link_libraries(move_my_turtle ${catkin_LIBRARIES})

#add_executable(move_my_turtlebot src/move_my_turtlebot.cpp)
#target_link_libraries(move_my_turtlebot ${catkin_LIBRARIES})

#add_executable(move_my_turtlebot2 src/move_my_turtlebot2.cpp)
#target_link_libraries(move_my_turtlebot2 ${catkin_LIBRARIES})

#add_executable(example_srv_request src/example_srv_request.cpp)
#target_link_libraries(example_srv_request ${catkin_LIBRARIES})

#add_executable(example_srv_response src/example_srv_response.cpp)
#target_link_libraries(example_srv_response ${catkin_LIBRARIES})

#add_executable(example_talker_msg src/example_talker_msg.cpp)
#target_link_libraries(example_talker_msg ${catkin_LIBRARIES})

#add_executable(example_listener_msg src/example_listener_msg.cpp)
#target_link_libraries(example_listener_msg ${catkin_LIBRARIES})

#add_executable(bhand_test src/bhand_test.cpp)
#target_link_libraries(bhand_test ${catkin_LIBRARIES})

#add_executable(bhand_pose_monitor src/bhand_pose_monitor.cpp)
#target_link_libraries(bhand_pose_monitor ${catkin_LIBRARIES})
# add_executable(can_test src/can_test.cpp)
# target_link_libraries(can_test ${catkin_LIBRARIES})
# target_link_libraries(can_test ${CMAKE_DL_LIBS})
# 
# add_executable(pcan_test src/pcan_test.cpp)
# target_link_libraries(pcan_test ${catkin_LIBRARIES})
# target_link_libraries(pcan_test ${CMAKE_DL_LIBS})
# 
# add_executable(bhand_force_control src/bhand_force_control.cpp)
# target_link_libraries(bhand_force_control ${catkin_LIBRARIES})
# 
# add_executable(keyboard_control src/keyboard_control.cpp)
# target_link_libraries(keyboard_control ${catkin_LIBRARIES})
# 
# add_executable(pipe_fifo_server src/pipe_fifo_server.cpp)
# add_executable(pipe_fifo_client src/pipe_fifo_client.cpp)
# target_link_libraries(pipe_fifo_server ${catkin_LIBRARIES})
# target_link_libraries(pipe_fifo_client ${catkin_LIBRARIES})

add_executable(ge_test src/ge_test.cpp)
target_link_libraries(ge_test ${catkin_LIBRARIES})

add_executable(ge_test_base src/ge_test_base.cpp)
target_link_libraries(ge_test_base ${catkin_LIBRARIES})

add_executable(ge_test_fetchmulti_large src/ge_test_fetchmulti_large.cpp)
target_link_libraries(ge_test_fetchmulti_large ${catkin_LIBRARIES})

add_executable(ge_test_old src/ge_test_old.cpp)
target_link_libraries(ge_test_old ${catkin_LIBRARIES})

add_executable(ge_test_fetchmulti src/ge_test_fetchmulti.cpp)
target_link_libraries(ge_test_fetchmulti ${catkin_LIBRARIES})

add_executable(fine_tuning src/fine_tuning.cpp)
target_link_libraries(fine_tuning ${catkin_LIBRARIES})

add_executable(ge_test_jdc src/ge_test_jdc.cpp)
target_link_libraries(ge_test_jdc ${catkin_LIBRARIES})

add_executable(ge_test_new src/ge_test_hxn.cpp)
target_link_libraries(ge_test_new ${catkin_LIBRARIES})

add_executable(ge_test_arm src/ge_test_arm.cpp)
target_link_libraries(ge_test_arm ${catkin_LIBRARIES})

# add_executable(bhand_notice_position src/bhand_notice_position.cpp)
# target_link_libraries(bhand_notice_position ${catkin_LIBRARIES})
# 
# add_executable(bhand_axis_force_limit src/bhand_axis_force_limit.cpp)
# target_link_libraries(bhand_axis_force_limit ${catkin_LIBRARIES})
# target_link_libraries(bhand_axis_force_limit ${CMAKE_DL_LIBS})
