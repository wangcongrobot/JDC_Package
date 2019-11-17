#!/bin/bash

echo "A" | sudo -S chmod 777 /dev/ttyUSB*
cd ~/qt_ui_test/build-hapticpaint-Desktop_Qt_5_5_1_GCC_64bit-Release
./hapticpaint
