#include "husky_highlevel_controller_ex_4/Scan2.hpp"

namespace husky_highlevel_controller_ex_4 {

	Scan2::Scan2() {
		scan_pub = n.advertise<sensor_msgs::LaserScan>("/scan2", 1);
		scan_sub = n.subscribe<sensor_msgs::LaserScan>("/scan", 1, &Scan2::scanCallback, this);
	}

	void Scan2::scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan2) {
		int ranges = scan2->ranges.size();

		sensor_msgs::LaserScan scan;
		scan.header.stamp = scan2->header.stamp;
		scan.header.frame_id = scan2->header.frame_id;
		scan.angle_min = scan2->angle_min;
		scan.angle_max = scan2->angle_max;
		scan.angle_increment = scan2->angle_increment;
		scan.time_increment = scan2->time_increment;
		scan.range_min = 0.0;
		scan.range_max = 100.0;

		scan.ranges.resize(ranges);
		for (int i = 0; i < ranges; ++i) {
			scan.ranges[i] = scan2->ranges[i] > 30.0 ? 30.0 : scan2->ranges[i];
			
			ROS_INFO_STREAM("ROS_INFO_STREAM /Scan2 laser range values (m) :" << scan.ranges[i]);
		}

		ROS_INFO_STREAM("ROS_INFO_STREAM maximum laser distance (m) : " << scan.range_max);


		scan_pub.publish(scan);
	}

	Scan2::~Scan2() {}

} /* namespace */