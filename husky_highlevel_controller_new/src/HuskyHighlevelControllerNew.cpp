#include "husky_highlevel_controller_new/HuskyHighlevelControllerNew.hpp"

namespace husky_highlevel_controller_new {

HuskyHighlevelControllerNew::HuskyHighlevelControllerNew(ros::NodeHandle& nodeHandle) :
  nodeHandle_(nodeHandle) {

  }

// exercise 2-6: create a callback method to record the minimum distance of scan range
void HuskyHighlevelControllerNew::scanCallback(const sensor_msgs::LaserScan &scan_msg) {
	float smallest_distance = 100;
	// the angle corresponding to the minimum distance

	// number of the elements in ranges array
	int arr_size = floor((scan_msg.angle_max - scan_msg.angle_min) / scan_msg.angle_increment);

	for (int i = 0; i < arr_size; i++) smallest_distance = scan_msg.ranges[i] < smallest_distance ? scan_msg.ranges[i] : smallest_distance;


	// three different approaches to display the information in the console
	std::cout << "cout minimum laser distance (m) : " << smallest_distance << std::endl;
	ROS_INFO_STREAM("ROS_INFO_STREAM minimum laser distance (m) : %f" << smallest_distance);
	ROS_INFO("ROS_INFO minimum laser distance (m) : %f", smallest_distance);
}

HuskyHighlevelControllerNew::~HuskyHighlevelControllerNew() {}

} /* namespace */