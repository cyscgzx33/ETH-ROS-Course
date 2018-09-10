#include <ros/ros.h>
#include "husky_highlevel_controller_new/HuskyHighlevelControllerNew.hpp"
#include "husky_highlevel_controller_new/Scan2.hpp"

int main(int argc, char** argv) {

	// ros::init(argc, argv, "my_node_name")
	ros::init(argc, argv, "husky_highlevel_controller_new");
	// nodeHandle("~") means privete nodeHandle
	ros::NodeHandle nodeHandle("~");

	husky_highlevel_controller_new::Scan2 scan2;

	// create an instance huskyHighlevelControllerNew for husky_highlevel_controller_new::HuskyHighlevelControllerNew
	husky_highlevel_controller_new::HuskyHighlevelControllerNew huskyHighlevelControllerNew(nodeHandle);

	// ros::spin() is a common way of callbacks
	ros::spin();

	return 0;
}