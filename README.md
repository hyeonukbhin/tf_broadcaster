TF2 Broadcaster for KIST Environment between Simonpic and Silbot
===========================================================

## Description

Connecting package between /map(silbot's coordinate system)and /simonpic(simonpic's coordinate system)

## 2. Guidance for Anastasiya


Kist_tf2 pakcage in this repository is a previous version of our environment.

kist_tf2 package's usage is below
'''
rosrun kist_tf2 kist_tf2_multi_br_node 
rosrun kist_tf2 kist_tf2_lis_node 
'''
Refer to this to create a node broadcasting for TF.

You can use both C ++ and python languages.

Please check the reference below.

I have prepared a rosbag file for you.

This is a rosbag with real human's position recorded.

Use the following command for repeat playback.
'''
rosbag play -l simonpic_test_200414.bag
'''
and you can see image in the rosbag using rqt_image_view package
![](assets/simonpic_test.gif)


## 3. Reference
- ["ROS TF2 Tutorials"](http://wiki.ros.org/tf2/Tutorials).

- [Writing a tf2 static broadcaster (Python)](http://wiki.ros.org/tf2/Tutorials/Writing%20a%20tf2%20static%20broadcaster%20%28Python%29)
This tutorial teaches you how to broadcast static coordinate frames to tf2

- [Writing a tf2 listener (Python)](http://wiki.ros.org/tf2/Tutorials/Writing%20a%20tf2%20listener%20%28Python%29)
This tutorial teaches you how to use tf2 to get access to frame transformations.

- [Writing a tf2 static broadcaster (C++)](http://wiki.ros.org/tf2/Tutorials/Writing%20a%20tf2%20static%20broadcaster%20%28C%2B%2B%29)
This tutorial teaches you how to broadcast static coordinate frames to tf2

- [Writing a tf2 listener (C++)](http://wiki.ros.org/tf2/Tutorials/Writing%20a%20tf2%20listener%20%28C%2B%2B%29)
This tutorial teaches you how to use tf2 to get access to frame transformations.
