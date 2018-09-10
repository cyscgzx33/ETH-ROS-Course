#include "husky_highlevel_controller_new/HuskyHighlevelControllerNew.hpp"

namespace husky_highlevel_controller_new {

HuskyHighlevelControllerNew::HuskyHighlevelControllerNew(ros::NodeHandle& nodeHandle) :
  nodeHandle_(nodeHandle) {
  	// to obtain the params by calling getParam()
  	nodeHandle.getParam("/husky_highlevel_controller_new/scan_subscriber_topic", scan_subscriber_topic);
  	nodeHandle.getParam("/husky_highlevel_controller_new/scan_subscriber_queue_size", scan_subscriber_queue_size);

	// Exercise 2-5: Create a subscriber to the /scan topic.
	// Exercise 2-6: create a callback method to record the minimum distance of scan range

	scan_subscriber_ = nodeHandle_.subscribe(scan_subscriber_topic, scan_subscriber_queue_size, &HuskyHighlevelControllerNew::scanCallback, this);
		ROS_INFO("Successfully launch node");
    }

// exercise 2-6: create a callback method to record the minimum distance of scan range
void HuskyHighlevelControllerNew::scanCallback(const sensor_msgs::LaserScan &scan_msg) {
	float smallest_distance = 30;
	// the angle corresponding to the minimum distance
	
	// number of the elements in ranges array
	/*int arr_size = floor((scan_msg.angle_max - scan_msg.angle_min) / scan_msg.angle_increment);*/
	std::vector<float> ranges = scan_msg.ranges;
	for (float vec:ranges) {
		if (smallest_distance > vec) smallest_distance = vec;
		/*ROS_INFO_STREAM("ROS_INFO_STREAM laser range values (m) :" << vec);*/
	}	



	/*for (int i = 0; i < ranges.size(); i++) {
		smallest_distance = smallest_distance > scan_msg.ranges[i] ? scan_msg.ranges[i] : smallest_distance;
		scan_msg.ranges[i] = scan_msg.ranges[i] > 100 ? 100 : scan_msg.ranges[i];
		ROS_INFO_STREAM("ROS_INFO_STREAM laser range values (m) :" << scan_msg.ranges[i]);
	}
	*/
	/*for (int i = 0; i < arr_size; i++) smallest_distance = scan_msg.ranges[i] < smallest_distance ? scan_msg.ranges[i] : smallest_distance;*/

  	// three different approaches to display the information in the console
	/*std::cout << "cout minimum laser distance (m) : " << smallest_distance << std::endl;*/
	/*ROS_INFO_STREAM("ROS_INFO_STREAM minimum laser distance (m) : " << smallest_distance);
	ROS_INFO_STREAM("ROS_INFO_STREAM maximum laser distance (m) : " << scan_msg.range_max);
	ROS_INFO("ROS_INFO minimum laser distance (m) : %f", smallest_distance);*/
}

HuskyHighlevelControllerNew::~HuskyHighlevelControllerNew() {}

} /* namespace */