# CMake generated Testfile for 
# Source directory: /home/robot/catkin_ws/src/cv_bridge/test
# Build directory: /home/robot/catkin_ws/build/cv_bridge/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(_ctest_cv_bridge_gtest_cv_bridge-utest "/home/robot/catkin_ws/build/catkin_generated/env_cached.sh" "/usr/bin/python" "/opt/ros/indigo/share/catkin/cmake/test/run_tests.py" "/home/robot/catkin_ws/build/test_results/cv_bridge/gtest-cv_bridge-utest.xml" "--return-code" "/home/robot/catkin_ws/devel/lib/cv_bridge/cv_bridge-utest --gtest_output=xml:/home/robot/catkin_ws/build/test_results/cv_bridge/gtest-cv_bridge-utest.xml")
add_test(_ctest_cv_bridge_nosetests_enumerants.py "/home/robot/catkin_ws/build/catkin_generated/env_cached.sh" "/usr/bin/python" "/opt/ros/indigo/share/catkin/cmake/test/run_tests.py" "/home/robot/catkin_ws/build/test_results/cv_bridge/nosetests-enumerants.py.xml" "--return-code" "/usr/bin/cmake -E make_directory /home/robot/catkin_ws/build/test_results/cv_bridge" "/usr/bin/nosetests-2.7 -P --process-timeout=60 /home/robot/catkin_ws/src/cv_bridge/test/enumerants.py --with-xunit --xunit-file=/home/robot/catkin_ws/build/test_results/cv_bridge/nosetests-enumerants.py.xml")
