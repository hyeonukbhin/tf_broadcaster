#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_ros/transform_broadcaster.h>
#include <geometry_msgs/TransformStamped.h>
#include <turtlesim/Pose.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <tf2_msgs/TFMessage.h>
#include <simonpic_msgs/MultiPersons.h>

#include <string>
#include <stdio.h>
#include <sstream> 
#include <iostream>

using namespace std;

void tf2Callback(const geometry_msgs::Pose::ConstPtr& msg)
{
    cout << "Recieve robot pose" << endl;
    //const geometry_msgs::Pose &raw_data = msg->Pose;
    static tf2_ros::TransformBroadcaster br;
    geometry_msgs::TransformStamped transformStamped;

    transformStamped.header.stamp = ros::Time::now();    
    transformStamped.header.frame_id = "/map";
    transformStamped.child_frame_id = "/simonpic";
    //msg->position.x;
    transformStamped.transform.translation.x = 1.8;
    transformStamped.transform.translation.y = -2.3;
    transformStamped.transform.translation.z = 0.0;     
    tf2::Quaternion q; 
    q.setRPY(1.57, 0, 3.14);
    transformStamped.transform.rotation.x = q.x();
    transformStamped.transform.rotation.y = q.y();
    transformStamped.transform.rotation.z = q.z();
    transformStamped.transform.rotation.w = q.w();
    br.sendTransform(transformStamped);
}

void tf2PersonCallback(const simonpic_msgs::MultiPersons::ConstPtr& msg){
    cout << "Recieve human pose" << endl;
    static tf2_ros::TransformBroadcaster br;
    geometry_msgs::TransformStamped transformStamped;
    tf2_msgs::TFMessage transformArray;
    tf2::Quaternion q; 
    transformArray.transforms.clear();

    for(size_t i=0; i<msg->persons.size(); ++i)
    {  
	string child_frame_id;
        const simonpic_msgs::Person &raw_data = msg->persons[i];
	if(raw_data.name.data == "")
	{
            child_frame_id = raw_data.id.data;
	}
	else if(raw_data.name.data == "kr")
        {
            child_frame_id = "Lee, K. R.";
        }
	else if(raw_data.name.data == "Taemin")
        {
            child_frame_id = "Choi, T. M.";
        }
	else if(raw_data.name.data == "HU")
        {
            child_frame_id = "Bhin, H. U.";
        }
	else if(raw_data.name.data == "HWJeon")
        {
            child_frame_id = "Jeon, H. W.";
        }
	else
	{
            child_frame_id = raw_data.name.data;	    
	}
        
        //string pg;    
        //stringstream s;
        //s << raw_data.id;
        //pg = s.str();
        //child_frame_id.append(pg);
        //cout << child_frame_id << "\n"; 
  
        transformStamped.header.stamp = ros::Time::now();    
        transformStamped.header.frame_id = "/simonpic";
        transformStamped.child_frame_id = child_frame_id;
        transformStamped.transform.translation.x = raw_data.location.x;
        transformStamped.transform.translation.y = raw_data.location.y;
        transformStamped.transform.translation.z = raw_data.location.z;     
        q.setRPY(0, 0, 0);
        transformStamped.transform.rotation.x = q.x();
        transformStamped.transform.rotation.y = q.y();
        transformStamped.transform.rotation.z = q.z();
        transformStamped.transform.rotation.w = q.w();
        transformArray.transforms.push_back(transformStamped);
        //br.sendTransform(transformArray.transforms[i]);
    }  

    br.sendTransform(transformArray.transforms); 
}

int main(int argc, char** argv){
    ros::init(argc, argv, "kist_tf2_br");
    cout << "Start kist_tf2_br node!!" << endl;

    ros::NodeHandle node;
    ros::Subscriber silbotPose_sub = node.subscribe("/robot_pose", 10,  &tf2Callback);
    ros::Subscriber personPose_sub = node.subscribe("/two_w/who", 10,  &tf2PersonCallback);

    ros::spin();
    return 0;
};
