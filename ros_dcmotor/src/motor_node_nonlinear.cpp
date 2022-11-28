#include <ros/ros.h>
#include <ros_dcmotor/pubsub_samenode.h>
#include <std_msgs/Float64.h>

double time_old;
double time_new;

double Ts;
double a = 27.65;
double b = 17.35;
double c = 5.635;

double w_now = 0;
double w_old = 0;
double voltage = 0;

template <typename T> int name_of_function_sign(T val) {
    return (T(0) < val) - (val < T(0));
}

template<>
void PublisherSubscriber<std_msgs::Float64, std_msgs::Float64>::subscriberCallback(const std_msgs::Float64::ConstPtr& recievedMsg)
{
	voltage = recievedMsg->data;

	time_new = ros::Time::now().toSec();

	Ts = time_new - time_old;
	
	w_now = (1-(a*Ts))*w_old - c*Ts*name_of_function_sign(w_old)  + b*Ts*voltage;
	ROS_INFO("%f",w_now);

	std_msgs::Float64 pubdata;

	pubdata.data = w_now;
	publisherObject.publish(pubdata);

	w_old = w_now;
	time_old = time_new;
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "motor_node");
	
	ROS_INFO("Starting");
	PublisherSubscriber<std_msgs::Float64, std_msgs::Float64> whatevername("omega", "voltage",1);
	time_old = ros::Time::now().toSec();
	time_new = ros::Time::now().toSec();
	ros::spin();
}