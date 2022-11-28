#ifndef PUBLISHER_SUBSCRIBER_H 
#define PUBLISHER_SUBSCRIBER_H  
#include <ros/ros.h> 
#include <string>

template<typename Publish_Topic, typename Subscribe_Topic> class PublisherSubscriber
{ 
public: 	
	PublisherSubscriber(){};
	PublisherSubscriber(std::string publishTopicName,std::string subscribeTopicName, int queueSize)
	{
		publisherObject = nH.advertise<Publish_Topic>(publishTopicName,queueSize);
		subscriberObject = nH.subscribe<Subscribe_Topic>(subscribeTopicName,queueSize,&PublisherSubscriber::subscriberCallback,this);
	};

	void subscriberCallback(const typename Subscribe_Topic::ConstPtr& recievedMsg);
protected: 	
	ros::Subscriber subscriberObject;
	ros::Publisher publisherObject;
	ros::NodeHandle nH;
};  
#endif