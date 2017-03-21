#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "std_msgs/Float32.h"

ros::Publisher share;
void call_back(const sensor_msgs::LaserScan::ConstPtr& msg){
    int n=(msg->angle_max-msg->angle_min)/msg->angle_increment;
    float min_range=msg->ranges[0];
    
    for(int i=1;i<n;i++){
		if(min_range>msg->ranges[i])min_range=msg->ranges[i];
	}
	std_msgs::Float32 ms;
	ms.data=min_range;
	share.publish(ms);
	
	
}

int main(int argc,char** argv){
	
	ros::init(argc,argv,"dist_laser");
	ros::NodeHandle l;
	
	ros::Subscriber sub=l.subscribe("base_scan",1000,call_back);
    share = l.advertise<std_msgs::Float32>("catter", 1000);
    
	ros::spin();
	return 0;
}
