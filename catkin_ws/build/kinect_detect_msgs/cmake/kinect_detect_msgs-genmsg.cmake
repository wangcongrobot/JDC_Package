# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "kinect_detect_msgs: 3 messages, 0 services")

set(MSG_I_FLAGS "-Ikinect_detect_msgs:/home/robot/catkin_ws/src/kinect_detect_msgs/msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(kinect_detect_msgs_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/robot/catkin_ws/src/kinect_detect_msgs/msg/ObjectIDs.msg" NAME_WE)
add_custom_target(_kinect_detect_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "kinect_detect_msgs" "/home/robot/catkin_ws/src/kinect_detect_msgs/msg/ObjectIDs.msg" ""
)

get_filename_component(_filename "/home/robot/catkin_ws/src/kinect_detect_msgs/msg/ObjectPose.msg" NAME_WE)
add_custom_target(_kinect_detect_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "kinect_detect_msgs" "/home/robot/catkin_ws/src/kinect_detect_msgs/msg/ObjectPose.msg" ""
)

get_filename_component(_filename "/home/robot/catkin_ws/src/kinect_detect_msgs/msg/ObjectPoses.msg" NAME_WE)
add_custom_target(_kinect_detect_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "kinect_detect_msgs" "/home/robot/catkin_ws/src/kinect_detect_msgs/msg/ObjectPoses.msg" "kinect_detect_msgs/ObjectPose"
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(kinect_detect_msgs
  "/home/robot/catkin_ws/src/kinect_detect_msgs/msg/ObjectIDs.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/kinect_detect_msgs
)
_generate_msg_cpp(kinect_detect_msgs
  "/home/robot/catkin_ws/src/kinect_detect_msgs/msg/ObjectPose.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/kinect_detect_msgs
)
_generate_msg_cpp(kinect_detect_msgs
  "/home/robot/catkin_ws/src/kinect_detect_msgs/msg/ObjectPoses.msg"
  "${MSG_I_FLAGS}"
  "/home/robot/catkin_ws/src/kinect_detect_msgs/msg/ObjectPose.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/kinect_detect_msgs
)

### Generating Services

### Generating Module File
_generate_module_cpp(kinect_detect_msgs
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/kinect_detect_msgs
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(kinect_detect_msgs_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(kinect_detect_msgs_generate_messages kinect_detect_msgs_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/robot/catkin_ws/src/kinect_detect_msgs/msg/ObjectIDs.msg" NAME_WE)
add_dependencies(kinect_detect_msgs_generate_messages_cpp _kinect_detect_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/robot/catkin_ws/src/kinect_detect_msgs/msg/ObjectPose.msg" NAME_WE)
add_dependencies(kinect_detect_msgs_generate_messages_cpp _kinect_detect_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/robot/catkin_ws/src/kinect_detect_msgs/msg/ObjectPoses.msg" NAME_WE)
add_dependencies(kinect_detect_msgs_generate_messages_cpp _kinect_detect_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(kinect_detect_msgs_gencpp)
add_dependencies(kinect_detect_msgs_gencpp kinect_detect_msgs_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS kinect_detect_msgs_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(kinect_detect_msgs
  "/home/robot/catkin_ws/src/kinect_detect_msgs/msg/ObjectIDs.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/kinect_detect_msgs
)
_generate_msg_lisp(kinect_detect_msgs
  "/home/robot/catkin_ws/src/kinect_detect_msgs/msg/ObjectPose.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/kinect_detect_msgs
)
_generate_msg_lisp(kinect_detect_msgs
  "/home/robot/catkin_ws/src/kinect_detect_msgs/msg/ObjectPoses.msg"
  "${MSG_I_FLAGS}"
  "/home/robot/catkin_ws/src/kinect_detect_msgs/msg/ObjectPose.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/kinect_detect_msgs
)

### Generating Services

### Generating Module File
_generate_module_lisp(kinect_detect_msgs
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/kinect_detect_msgs
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(kinect_detect_msgs_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(kinect_detect_msgs_generate_messages kinect_detect_msgs_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/robot/catkin_ws/src/kinect_detect_msgs/msg/ObjectIDs.msg" NAME_WE)
add_dependencies(kinect_detect_msgs_generate_messages_lisp _kinect_detect_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/robot/catkin_ws/src/kinect_detect_msgs/msg/ObjectPose.msg" NAME_WE)
add_dependencies(kinect_detect_msgs_generate_messages_lisp _kinect_detect_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/robot/catkin_ws/src/kinect_detect_msgs/msg/ObjectPoses.msg" NAME_WE)
add_dependencies(kinect_detect_msgs_generate_messages_lisp _kinect_detect_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(kinect_detect_msgs_genlisp)
add_dependencies(kinect_detect_msgs_genlisp kinect_detect_msgs_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS kinect_detect_msgs_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(kinect_detect_msgs
  "/home/robot/catkin_ws/src/kinect_detect_msgs/msg/ObjectIDs.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/kinect_detect_msgs
)
_generate_msg_py(kinect_detect_msgs
  "/home/robot/catkin_ws/src/kinect_detect_msgs/msg/ObjectPose.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/kinect_detect_msgs
)
_generate_msg_py(kinect_detect_msgs
  "/home/robot/catkin_ws/src/kinect_detect_msgs/msg/ObjectPoses.msg"
  "${MSG_I_FLAGS}"
  "/home/robot/catkin_ws/src/kinect_detect_msgs/msg/ObjectPose.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/kinect_detect_msgs
)

### Generating Services

### Generating Module File
_generate_module_py(kinect_detect_msgs
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/kinect_detect_msgs
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(kinect_detect_msgs_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(kinect_detect_msgs_generate_messages kinect_detect_msgs_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/robot/catkin_ws/src/kinect_detect_msgs/msg/ObjectIDs.msg" NAME_WE)
add_dependencies(kinect_detect_msgs_generate_messages_py _kinect_detect_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/robot/catkin_ws/src/kinect_detect_msgs/msg/ObjectPose.msg" NAME_WE)
add_dependencies(kinect_detect_msgs_generate_messages_py _kinect_detect_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/robot/catkin_ws/src/kinect_detect_msgs/msg/ObjectPoses.msg" NAME_WE)
add_dependencies(kinect_detect_msgs_generate_messages_py _kinect_detect_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(kinect_detect_msgs_genpy)
add_dependencies(kinect_detect_msgs_genpy kinect_detect_msgs_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS kinect_detect_msgs_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/kinect_detect_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/kinect_detect_msgs
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(kinect_detect_msgs_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/kinect_detect_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/kinect_detect_msgs
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(kinect_detect_msgs_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/kinect_detect_msgs)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/kinect_detect_msgs\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/kinect_detect_msgs
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(kinect_detect_msgs_generate_messages_py std_msgs_generate_messages_py)
endif()
