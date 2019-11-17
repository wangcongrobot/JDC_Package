#!/bin/bash

roslaunch bhand_controller bhand_controller.launch &
sleep 8
echo "bhand controller starting success!"

roslaunch beginner_tutorials bhand_force_control.launch &
sleep 0.1
wait
exit 0
