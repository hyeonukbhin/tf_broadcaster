#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_ros/transform_broadcaster.h>
#include <geometry_msgs/TransformStamped.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/Pose.h>
#include <std_msgs/String.h>
#include <std_msgs/Float64.h>
#include <tf2_msgs/TFMessage.h>
#include <json/json.h>
#include <json/jsoncpp.cpp>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream> 
#include <iostream>

using namespace std;

string json_str;

bool comparation_header(const std_msgs::String::ConstPtr& jsonEncodedResult_Input)
{
    // Convert to json
    json_str = jsonEncodedResult_Input->data.c_str(); //std_msgs::String -> std::string

    // Parser
	Json::Reader reader;
	Json::Value input_root;
	// Error check
	bool parsingRet = reader.parse(json_str, input_root);
	if (!parsingRet)
	{
		std::cout << "Failed to parse Json : " << reader.getFormattedErrorMessages();
		return false;
	}

	Json::Value header;
	header = input_root["header"];

    if (header["source"] == "KIST") //&& header["content"] == "human_recognition"
        return true;
    else 
        return false;

}

void tf2Callback(const geometry_msgs::Pose::ConstPtr& msg)
{
    cout << "Recieving robot pose" << endl;
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

void tf2PersonCallback(const std_msgs::String::ConstPtr& jsonEncodedResult_Input)
{
    cout << "Recieving human pose" << endl;
    if(comparation_header(jsonEncodedResult_Input) == true)
    {     
        // Convert to json
        json_str = jsonEncodedResult_Input->data.c_str(); //std_msgs::String -> std::string
        // Parser
        Json::Reader reader;
        Json::Value input_root;
        // Error check
        bool parsingRet = reader.parse(json_str, input_root);
        if (!parsingRet)
        {
            std::cout << "Failed to parse Json : " << reader.getFormattedErrorMessages();
            return;
        }

        Json::Value input_human_recognition;
        input_human_recognition = input_root["human_recognition"];

        if(input_human_recognition["frame_id"] != "")
        {
            float loc_x = input_human_recognition["loc_x"].asFloat();
            float loc_y = input_human_recognition["loc_y"].asFloat();
            float loc_z = input_human_recognition["loc_z"].asFloat();
            cout << "human_recogniton (loc_x, loc_y, loc_z) = " << " ( " << loc_x << " , "<< loc_y << " , " << loc_z << " ) " << endl;

            static tf2_ros::TransformBroadcaster br;
            geometry_msgs::TransformStamped transformStamped;

            transformStamped.header.stamp = ros::Time::now();    
            transformStamped.header.frame_id = "/simonpic";
            transformStamped.child_frame_id = "/human";
            transformStamped.transform.translation.x = loc_x;
            transformStamped.transform.translation.y = loc_y;
            transformStamped.transform.translation.z = loc_z;  
            tf2::Quaternion q; 
            q.setRPY(0, 0, 0);
            transformStamped.transform.rotation.x = q.x();
            transformStamped.transform.rotation.y = q.y();
            transformStamped.transform.rotation.z = q.z();
            transformStamped.transform.rotation.w = q.w();
            br.sendTransform(transformStamped);
        }  
    }
}
        
int main(int argc, char** argv){
    ros::init(argc, argv, "kist_tf2_br");

    ros::NodeHandle node;
    ros::Subscriber silbotPose_sub = node.subscribe("/robot_pose", 10,  &tf2Callback);
    ros::Subscriber personPose_sub = node.subscribe("/recognitionResult", 10,  &tf2PersonCallback);
  
    ros::spin();
    return 0;
};
