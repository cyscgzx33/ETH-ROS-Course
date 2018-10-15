#include "husky_highlevel_controller_ex_5/HuskyHighlevelControllerEx5.hpp"

namespace husky_highlevel_controller_ex_5 {

HuskyHighlevelControllerEx5::HuskyHighlevelControllerEx5(ros::NodeHandle& nodeHandle) :
  nodeHandle_(nodeHandle) {
	
  	// to obtain the params by calling getParam()
  	nodeHandle.getParam("/husky_highlevel_controller_ex_5/scan_subscriber_topic", scan_subscriber_topic);
  	nodeHandle.getParam("/husky_highlevel_controller_ex_5/scan_subscriber_queue_size", scan_subscriber_queue_size);
  	nodeHandle.getParam("/husky_highlevel_controller_ex_5/cmd_pub_topic", cmd_pub_topic);
   	nodeHandle.getParam("/husky_highlevel_controller_ex_5/cmd_pub_queue_size", cmd_pub_queue_size);
   	nodeHandle.getParam("/husky_highlevel_controller_ex_5/visualization_pub_queue_size", visualization_pub_queue_size);
   	nodeHandle.getParam("/husky_highlevel_controller_ex_5/visualization_pub_topic", visualization_pub_topic);
   	nodeHandle.getParam("/husky_highlevel_controller_ex_5/red_value", red_value);
   	nodeHandle.getParam("/husky_highlevel_controller_ex_5/green_value", green_value);
   	nodeHandle.getParam("/husky_highlevel_controller_ex_5/blue_value", blue_value);
   	nodeHandle.getParam("/husky_highlevel_controller_ex_5/zPosPillar", zPosPillar);

 	// definity need to advertise a publisher otherwise it didn't show up at the system
	scan_subscriber_ = nodeHandle_.subscribe(scan_subscriber_topic, scan_subscriber_queue_size, &HuskyHighlevelControllerEx5::scanCallback, this);
	cmd_pub_ = nodeHandle_.advertise<geometry_msgs::Twist>(cmd_pub_topic, cmd_pub_queue_size);
	pillar_visualization_pub_ = nodeHandle_.advertise<visualization_msgs::Marker>(visualization_pub_topic, visualization_pub_queue_size);


	ROS_INFO("Successfully launch node");
}


bool HuskyHighlevelControllerEx5::readParams() {
	if (!nodeHandle_.getParam("/husky_highlevel_controller_ex_5/scan_subscriber_topic", scan_subscriber_topic)) {
		ROS_ERROR("Could not find scan_subscriber_topic parameter!");
		return false;
	}

	if (!nodeHandle_.getParam("/husky_highlevel_controller_ex_5/scan_subscriber_queue_size", scan_subscriber_queue_size)) {
		ROS_ERROR("Could not find scan_subscriber_queue_size parameter!");
		return false;
	}

	return true;

}


void HuskyHighlevelControllerEx5::scanCallback(const sensor_msgs::LaserScan &scan_msg) {
	smallest_distance = 30;
	
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

	// Ex-5 Added: if start_move flag is false then all the velocity should be zero
	if (!start_move) {
		vel_msg_.linear.x = 0.0;
		vel_msg_.angular.z = 0.0;
	}

	cmd_pub_.publish(vel_msg_);


	// call the function pillar_visualization() to visualiza the position of the pillar
	pillar_visualization();

	// check out the output signals
	ROS_INFO_STREAM("X position of pillar (m) : " << xPosPillar);
	ROS_INFO_STREAM("Y position of pillar (m) : " << yPosPillar);
	ROS_INFO_STREAM("angular position of pillar (rad) : " << phiAnglePillar);

	ROS_INFO_STREAM("vel_msg_.linear.x : " << vel_msg_.linear.x);
	ROS_INFO_STREAM("vel_msg_.angular.z : " << vel_msg_.angular.z);
}

bool HuskyHighlevelControllerEx5::serviceCallback(std_srvs::SetBool::Request & request, std_srvs::SetBool::Response & response) {

	if (request.data) start_move = true;
	else start_move = false;
	response.success = true;

	ROS_INFO("request: %i", request.data);
	ROS_INFO("sending back response: [%i]", response.success);

	return true;
	
}


void HuskyHighlevelControllerEx5::pillar_visualization() {

	visualization_msgs::Marker marker;
	marker.header.frame_id = "base_laser";
	marker.header.stamp = ros::Time();
	marker.ns = "my_namespace";
	marker.id = 0;
	marker.type = visualization_msgs::Marker::SPHERE;
	marker.action = visualization_msgs::Marker::ADD;
	marker.pose.position.x = xPosPillar;
	marker.pose.position.y = yPosPillar;
	marker.pose.position.z = zPosPillar;
	marker.pose.orientation.x = 0.0;
	marker.pose.orientation.y = 0.0;
	marker.pose.orientation.z = 0.0;
	marker.pose.orientation.w = 0.0;
	marker.scale.x = 1;
	marker.scale.y = 1;
	marker.scale.z = 1;
	marker.color.a = 1.0; // remember to set the alpha
	marker.color.r = red_value; 
	marker.color.g = green_value; 
	marker.color.b = blue_value; 

	// only implement it when using a MESH_RESOURCE marker type
	marker.mesh_resource = "package://pr2_description//meshes/base_v0/base.dae";
	pillar_visualization_pub_.publish(marker);
}


HuskyHighlevelControllerEx5::~HuskyHighlevelControllerEx5() {}

} /* namespace */
