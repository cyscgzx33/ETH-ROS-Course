#include "husky_highlevel_controller_ex_3/HuskyHighlevelControllerEx3.hpp"

namespace husky_highlevel_controller_ex_3 {

HuskyHighlevelControllerEx3::HuskyHighlevelControllerEx3(ros::NodeHandle& nodeHandle) :
  nodeHandle_(nodeHandle) {
  	// to obtain the params by calling getParam()
  	nodeHandle.getParam("/husky_highlevel_controller_ex_3/scan_subscriber_topic", scan_subscriber_topic);
  	nodeHandle.getParam("/husky_highlevel_controller_ex_3/scan_subscriber_queue_size", scan_subscriber_queue_size);
  	nodeHandle.getParam("/husky_highlevel_controller_ex_3/cmd_pub_topic", cmd_pub_topic);
   	nodeHandle.getParam("/husky_highlevel_controller_ex_3/cmd_pub_queue_size", cmd_pub_queue_size);
 	
 	// definity need to advertise a publisher otherwise it didn't show up at the system
	scan_subscriber_ = nodeHandle_.subscribe(scan_subscriber_topic, scan_subscriber_queue_size, &HuskyHighlevelControllerEx3::scanCallback, this);
	cmd_pub_ = nodeHandle_.advertise<geometry_msgs::Twist>(cmd_pub_topic, cmd_pub_queue_size);

	ROS_INFO("Successfully launch node");
    }


void HuskyHighlevelControllerEx3::scanCallback(const sensor_msgs::LaserScan &scan_msg) {
	float smallest_distance = 30;
	
	// number of the elements in ranges array
	std::vector<float> ranges = scan_msg.ranges;
	for (int i = 0; i < ranges.size(); i++) {
		if (smallest_distance > ranges[i]) {

			// to obtain the radical distance and angular distance of the pillar
			smallest_distance = ranges[i];
			phiAnglePillar = (scan_msg.angle_min + i * scan_msg.angle_increment);
		}
	}	

	xPosPillar = smallest_distance * cos(phiAnglePillar);
	yPosPillar = smallest_distance * sin(phiAnglePillar);


	// The P-controller to drive husky towards the pillar
	// propotional gains for linear velocity and angular velocity
	float p_gain_vel = 0.1;
	float p_gain_ang = 0.4;

	// a dummy value 0 for making sure it hit the pillar
	vel_msg_.linear.x = xPosPillar > 0.4 ? xPosPillar * p_gain_vel : 1.0;  
	vel_msg_.angular.z = xPosPillar > 0.4 ? (- yPosPillar * p_gain_ang) : 0;

	cmd_pub_.publish(vel_msg_);


	ROS_INFO_STREAM("X position of pillar (m) : " << xPosPillar);
	ROS_INFO_STREAM("Y position of pillar (m) : " << yPosPillar);
	ROS_INFO_STREAM("angular position of pillar (rad) : " << phiAnglePillar);

	// check out the output signals
	ROS_INFO_STREAM("vel_msg_.linear.x : " << vel_msg_.linear.x);
	ROS_INFO_STREAM("vel_msg_.angular.z : " << vel_msg_.angular.z);
}

HuskyHighlevelControllerEx3::~HuskyHighlevelControllerEx3() {}

} /* namespace */