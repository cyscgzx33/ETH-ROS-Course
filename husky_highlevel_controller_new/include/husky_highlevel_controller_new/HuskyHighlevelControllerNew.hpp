#pragma once
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>

namespace husky_highlevel_controller_new {
/*	
	Class containing the Husky Highlevel Controller (new)
*/
	class HuskyHighlevelControllerNew {
	public:
		/*
			Constructor.			
		*/
		HuskyHighlevelControllerNew(ros::NodeHandle& nodeHandle);

		// scanCallback function
		void scanCallback(const sensor_msgs::LaserScan &scan_msg);



		/*
			Destructor.			
		*/
		virtual ~HuskyHighlevelControllerNew();

	private:
		ros::NodeHandle nodeHandle_;
	};

} /*namespace*/