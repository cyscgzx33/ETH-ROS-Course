#pragma once

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include <visualization_msgs/Marker.h>
#include <tf/transform_listener.h>
#include <string>

namespace husky_highlevel_controller_ex_5 {
/*	
	Class containing the Husky Highlevel Controller (new)
*/
	class HuskyHighlevelControllerEx5 {
	public:
		/*
			Constructor.			
		*/
		HuskyHighlevelControllerEx5(ros::NodeHandle& nodeHandle);

		// scanCallback function
		void scanCallback(const sensor_msgs::LaserScan &scan_msg);

		/*
			Destructor.			
		*/
		virtual ~HuskyHighlevelControllerEx5();



	private:
		ros::NodeHandle nodeHandle_;
		ros::Subscriber scan_subscriber_;
		

		/*
		   parameter information 
		   linked to config.yaml
		*/
		std::string scan_subscriber_topic;
		std::string cmd_pub_topic;
		std::string visualization_pub_topic;
		int scan_subscriber_queue_size;
		int cmd_pub_queue_size;
		int visualization_pub_queue_size;
		float zPosPillar;
		float red_value;
		float green_value;
		float blue_value;


		// smallest distance from laser scan
		float smallest_distance;

		// Pillar Information
		float xPosPillar; // x position of pillar
		float yPosPillar; // y position of pillar
		float phiAnglePillar; // yaw angle towards pillar

		// Publishers
		ros::Publisher cmd_pub_; // a publisher to /cmd_vel
		ros::Publisher pillar_visualization_pub_; // a publisher to marker

		// (easy version of ex-3.7)
		// a function related to pillar visualization
		void pillar_visualization();

		// msgs: twist
		geometry_msgs::Twist vel_msg_;

		// (more difficult version of ex-3.7)
		// a TF listener to transform the extracted point from the laser frame to the odom frame
		tf::TransformListener tf_listener;

	};


} /*namespace*/