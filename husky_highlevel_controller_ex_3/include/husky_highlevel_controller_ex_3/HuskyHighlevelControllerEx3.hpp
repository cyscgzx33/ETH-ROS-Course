#pragma once
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include <string>

namespace husky_highlevel_controller_ex_3 {
/*	
	Class containing the Husky Highlevel Controller (new)
*/
	class HuskyHighlevelControllerEx3 {
	public:
		/*
			Constructor.			
		*/
		HuskyHighlevelControllerEx3(ros::NodeHandle& nodeHandle);

		// scanCallback function
		void scanCallback(const sensor_msgs::LaserScan &scan_msg);

		/*
			Destructor.			
		*/
		virtual ~HuskyHighlevelControllerEx3();



	private:
		ros::NodeHandle nodeHandle_;
		ros::Subscriber scan_subscriber_;
		

		// parameter information 
		// linked to config.yaml

		std::string scan_subscriber_topic;
		std::string cmd_pub_topic;
		int scan_subscriber_queue_size;
		int cmd_pub_queue_size;

		// Pillar Information

		float xPosPillar; // x position of pillar
		float yPosPillar; // y position of pillar
		float phiAnglePillar; // yaw angle towards pillar

		// Publishers: publisher to /cmd_vel
		ros::Publisher cmd_pub_;

		// msgs: twist
		geometry_msgs::Twist vel_msg_;

	};



} /*namespace*/