#!/usr/bin/env python
# -*- coding: utf-8 -*-
# creates a relay to a python script source file, acting as that file.
# The purpose is that of a symlink
with open("/home/robot/catkin_ws/src/object_recognition_core/apps/dbscripts/object_delete.py", 'r') as fh:
    exec(fh.read())
