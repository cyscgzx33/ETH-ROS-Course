#include <ros/ros.h>
#include "husky_highlevel_controller_ex_3/HuskyHighlevelControllerEx3.hpp"
#include "husky_highlevel_controller_ex_3/Scan2.hpp"

int main(int argc, char** argv) {

	// ros::init(argc, argv, "my_node_name")
	ros::init(argc, argv, "husky_highlevel_controller_ex_3");
	// nodeHandle("~") means privete nodeHandle
	ros::NodeHandle nodeHandle("~");

	husky_highlevel_controller_ex_3::Scan2 scan2;

	// create an instance HuskyHighlevelControllerEx3 for husky_highlevel_controller_ex_3::HuskyHighlevelControllerEx3
	husky_highlevel_controller_ex_3::HuskyHighlevelControllerEx3 HuskyHighlevelControllerEx3(nodeHandle);

	// ros::spin() is a common way of callbacks
	ros::spin();

	return 0;
}