#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_ros/transform_broadcaster.h>
#include <geometry_msgs/TransformStamped.h>

#include <string>
#include <stdio.h>
#include <sstream> 
#include <iostream>

using namespace std;

int main(int argc, char** argv){
    ros::init(argc, argv, "kist_tf2_lis");
    cout << "start kist_tf2_listener node!!" << "\n";
    ros::NodeHandle node;

    //ros::Publisher tf_markerData_pub = node.advertise<ros_realsense::markerDataArray>("tf_markerData", 10);

    tf2_ros::Buffer tfBuffer;
    tf2_ros::TransformListener tfListener(tfBuffer); // Important!!

    ros::Rate r(40);
    while(ros::ok())
    {
        geometry_msgs::TransformStamped transformStamped;
        try
        {
            transformStamped = tfBuffer.lookupTransform("base_link", "human", ros::Time(0));
        }   
        catch(tf2::TransformException &ex)
        {
            ROS_WARN("%s",ex.what());
            ros::Duration(1.0).sleep();
            continue;
        }  

        cout << "loc_x" << transformStamped.transform.translation.x << endl;

        ros::spinOnce();
        r.sleep();
    }
}

