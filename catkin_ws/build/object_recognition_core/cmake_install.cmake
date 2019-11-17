# Install script for directory: /home/robot/catkin_ws/src/object_recognition_core

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/robot/catkin_ws/build/object_recognition_core/catkin_generated/installspace/object_recognition_core.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/object_recognition_core/cmake" TYPE FILE FILES "/home/robot/catkin_ws/build/object_recognition_core/catkin_generated/installspace/test.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/object_recognition_core/cmake" TYPE FILE FILES
    "/home/robot/catkin_ws/build/object_recognition_core/catkin_generated/installspace/object_recognition_coreConfig.cmake"
    "/home/robot/catkin_ws/build/object_recognition_core/catkin_generated/installspace/object_recognition_coreConfig-version.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/object_recognition_core" TYPE FILE FILES "/home/robot/catkin_ws/src/object_recognition_core/package.xml")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  include("/home/robot/catkin_ws/build/object_recognition_core/catkin_generated/safe_execute_install.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "main")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/object_recognition_core" TYPE DIRECTORY FILES "/home/robot/catkin_ws/src/object_recognition_core/include/object_recognition_core/")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/object_recognition_core" TYPE PROGRAM FILES
    "/home/robot/catkin_ws/src/object_recognition_core/apps/detection"
    "/home/robot/catkin_ws/src/object_recognition_core/apps/training"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "main")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/object_recognition_core" TYPE DIRECTORY FILES "/home/robot/catkin_ws/src/object_recognition_core/apps/dbscripts" USE_SOURCE_PERMISSIONS)
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/robot/catkin_ws/build/object_recognition_core/python/cmake_install.cmake")
  include("/home/robot/catkin_ws/build/object_recognition_core/src/cmake_install.cmake")
  include("/home/robot/catkin_ws/build/object_recognition_core/web_ui/cmake_install.cmake")
  include("/home/robot/catkin_ws/build/object_recognition_core/share/cmake_install.cmake")
  include("/home/robot/catkin_ws/build/object_recognition_core/test/cmake_install.cmake")
  include("/home/robot/catkin_ws/build/object_recognition_core/doc/cmake_install.cmake")

endif()

