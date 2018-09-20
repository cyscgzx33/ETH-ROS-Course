#pragma once
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <string>

namespace husky_highlevel_controller_ex_3 {

	class Scan2 {
	public:
		Scan2();
		virtual ~Scan2();
		void scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan2);
	
	private:
		ros::NodeHandle n;
		ros::Publisher scan_pub;
		ros::Subscriber scan_sub;


		std::string scan_subscriber_topic;
		int scan_subscriber_queue_size;

	};
}