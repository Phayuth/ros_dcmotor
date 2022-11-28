#!/usr/bin/env python
import rospy
import math
from std_msgs.msg import Float64
from ros_dcmotor.msg import motor

class motor_node(object):
	def __init__(self):
		self.a = 27
		self.b = 17

		self.time_old = rospy.Time.now().to_sec()
		self.time_now = rospy.Time.now().to_sec()

		self.w_now = 0
		self.w_pre = 0
		self.voltage = 0

		rospy.Subscriber('/voltage',Float64,self.cb_voltage)            # subscribe to voltage
		self.omega_pub = rospy.Publisher("/omega",motor,queue_size=1) # publish rotation speed

	def cb_voltage(self,msg):

		self.voltage = msg.data

		self.time_now = rospy.Time.now().to_sec()

		Ts = (self.time_now - self.time_old)

		self.w_now = (1-(self.a*Ts))*self.w_pre + self.b*Ts*self.voltage
		
		data = motor()
		data.header.stamp = rospy.Time.now()
		data.header.frame_id = "right_motor"
		data.encoder = math.floor(self.w_now)
		self.omega_pub.publish(data)

		self.w_pre = self.w_now
		self.time_old = self.time_now

	def start(self):
		rospy.spin()

if __name__ == '__main__':
	rospy.init_node("ros_ros_dcmotor")
	task = motor_node()
	task.start()