cmake_minimum_required(VERSION 2.8.3)
project(simonpic_msgs)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  rospy
  sensor_msgs
  std_msgs
  geometry_msgs
  message_generation
)
## Generate messages in the 'msg' folder
add_message_files(
   FILES
   Person.msg
   MultiPersons.msg
   where_msgs.msg
   roilocation_msgs.msg
)


## Generate added messages and services with any dependencies listed here
generate_messages(
   DEPENDENCIES sensor_msgs std_msgs geometry_msgs
)

## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES simonpic_msgs
   CATKIN_DEPENDS rospy sensor_msgs std_msgs  message_runtime
#  DEPENDS system_lib
)

# include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
)
