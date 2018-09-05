#include <ros/ros.h>
#include "husky_highlevel_controller_new/HuskyHighlevelControllerNew.hpp"

int main(int argc, char** argv) {

	ros::init(argc, argv, "husky_highlevel_controller_new");
	// nodeHandle("~") means privete nodeHandle
	ros::NodeHandle nodeHandle("~");

	// create an instance huskyHighlevelControllerNew for husky_highlevel_controller_new::HuskyHighlevelControllerNew
	husky_highlevel_controller_new::HuskyHighlevelControllerNew huskyHighlevelControllerNew(nodeHandle);

	// Exercise 2-5: Create a subscriber to the /scan topic.
	// Exercise 2-6: create a callback method to record the minimum distance of scan range
	ros::Subscriber scan_subscriber_ = nodeHandle.subscribe("scan", 1, &husky_highlevel_controller_new::HuskyHighlevelControllerNew::scanCallback, &huskyHighlevelControllerNew);

	// ros::spin() is a common way of callbacks
	ros::spin();

	return 0;
}