# Install script for directory: /home/robot/catkin_ws/src/object_recognition_msgs

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/robot/catkin_ws/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/object_recognition_msgs/action" TYPE FILE FILES "/home/robot/catkin_ws/src/object_recognition_msgs/action/ObjectRecognition.action")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/object_recognition_msgs/msg" TYPE FILE FILES
    "/home/robot/catkin_ws/devel/share/object_recognition_msgs/msg/ObjectRecognitionAction.msg"
    "/home/robot/catkin_ws/devel/share/object_recognition_msgs/msg/ObjectRecognitionActionGoal.msg"
    "/home/robot/catkin_ws/devel/share/object_recognition_msgs/msg/ObjectRecognitionActionResult.msg"
    "/home/robot/catkin_ws/devel/share/object_recognition_msgs/msg/ObjectRecognitionActionFeedback.msg"
    "/home/robot/catkin_ws/devel/share/object_recognition_msgs/msg/ObjectRecognitionGoal.msg"
    "/home/robot/catkin_ws/devel/share/object_recognition_msgs/msg/ObjectRecognitionResult.msg"
    "/home/robot/catkin_ws/devel/share/object_recognition_msgs/msg/ObjectRecognitionFeedback.msg"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/object_recognition_msgs/srv" TYPE FILE FILES "/home/robot/catkin_ws/src/object_recognition_msgs/srv/GetObjectInformation.srv")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/object_recognition_msgs/msg" TYPE FILE FILES
    "/home/robot/catkin_ws/src/object_recognition_msgs/msg/ObjectType.msg"
    "/home/robot/catkin_ws/src/object_recognition_msgs/msg/ObjectInformation.msg"
    "/home/robot/catkin_ws/src/object_recognition_msgs/msg/RecognizedObject.msg"
    "/home/robot/catkin_ws/src/object_recognition_msgs/msg/RecognizedObjectArray.msg"
    "/home/robot/catkin_ws/src/object_recognition_msgs/msg/Table.msg"
    "/home/robot/catkin_ws/src/object_recognition_msgs/msg/TableArray.msg"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/object_recognition_msgs/cmake" TYPE FILE FILES "/home/robot/catkin_ws/build/object_recognition_msgs/catkin_generated/installspace/object_recognition_msgs-msg-paths.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/robot/catkin_ws/devel/include/object_recognition_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/robot/catkin_ws/devel/share/common-lisp/ros/object_recognition_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  execute_process(COMMAND "/usr/bin/python" -m compileall "/home/robot/catkin_ws/devel/lib/python2.7/dist-packages/object_recognition_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/robot/catkin_ws/devel/lib/python2.7/dist-packages/object_recognition_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/robot/catkin_ws/build/object_recognition_msgs/catkin_generated/installspace/object_recognition_msgs.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/object_recognition_msgs/cmake" TYPE FILE FILES "/home/robot/catkin_ws/build/object_recognition_msgs/catkin_generated/installspace/object_recognition_msgs-msg-extras.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/object_recognition_msgs/cmake" TYPE FILE FILES
    "/home/robot/catkin_ws/build/object_recognition_msgs/catkin_generated/installspace/object_recognition_msgsConfig.cmake"
    "/home/robot/catkin_ws/build/object_recognition_msgs/catkin_generated/installspace/object_recognition_msgsConfig-version.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/object_recognition_msgs" TYPE FILE FILES "/home/robot/catkin_ws/src/object_recognition_msgs/package.xml")
endif()

