#include <ros/ros.h>
#include <ros_dcmotor/pubsub_samenode.h>
#include <std_msgs/Float64.h>
#include <ros_dcmotor/motor.h>

ros::Time time_old;
ros::Time time_new;

double Ts;
double a = 27.65;
double b = 17.35;

double w_now = 0;
double w_old = 0;
double voltage = 0;


template<>
void PublisherSubscriber<ros_dcmotor::motor, std_msgs::Float64>::subscriberCallback(const std_msgs::Float64::ConstPtr& recievedMsg)
{
	voltage = recievedMsg->data;

	time_new = ros::Time::now();

	Ts = (time_new - time_old).toSec();
	
	w_now = (1-(a*Ts))*w_old + b*Ts*voltage;
	ROS_INFO("%f",w_now);

	ros_dcmotor::motor pubdata;
	pubdata.header.stamp = time_new;
	pubdata.header.frame_id = "motor_link";
	pubdata.speed = w_now;
	// pubdata.encoder = 0;
	publisherObject.publish(pubdata);

	w_old = w_now;
	time_old = time_new;
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "motor_node");
	
	ROS_INFO("Starting");
	PublisherSubscriber<ros_dcmotor::motor, std_msgs::Float64> whatevername("omega", "voltage",1);
	time_old = ros::Time::now();
	time_new = ros::Time::now();
	ros::spin();
}