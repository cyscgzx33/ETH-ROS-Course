#include <ros/ros.h>
#include "husky_highlevel_controller_ex_5/HuskyHighlevelControllerEx5.hpp"
#include "husky_highlevel_controller_ex_5/Scan2.hpp"

int main(int argc, char** argv) {

	// ros::init(argc, argv, "my_node_name")
	ros::init(argc, argv, "husky_highlevel_controller_ex_5");
	// nodeHandle("~") means privete nodeHandle
	ros::NodeHandle nodeHandle("~");

	husky_highlevel_controller_ex_5::Scan2 scan2;

	// create an instance HuskyHighlevelControllerEx5 for husky_highlevel_controller_ex_5::HuskyHighlevelControllerEx5
	husky_highlevel_controller_ex_5::HuskyHighlevelControllerEx5 HuskyHighlevelControllerEx5(nodeHandle);

	// ros::spin() is a common way of callbacks
	ros::spin();

	return 0;
}