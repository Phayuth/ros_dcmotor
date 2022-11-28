#!/usr/bin/env python
import rospy
import numpy as np
from std_msgs.msg import Float64


class motor(object):
	def __init__(self):
		self.a = 27.65
		self.b = 17.35
		self.c = 5.635

		self.time_old = rospy.Time.now().to_sec()
		self.time_now = rospy.Time.now().to_sec()

		self.w_now = 0
		self.w_pre = 0
		self.voltage = 0

		rospy.Subscriber('/voltage',Float64,self.cb_voltage)            # subscribe to voltage
		self.omega_pub = rospy.Publisher("/omega",Float64,queue_size=1) # publish rotation speed

	def cb_voltage(self,msg):

		self.voltage = msg.data

		self.time_now = rospy.Time.now().to_sec()

		Ts = (self.time_now - self.time_old)

		self.w_now = (1-(self.a*Ts))*self.w_pre + c*Ts*np.sign(w_pre) + self.b*Ts*self.voltage
		
		data = Float64()
		data.data = self.w_now
		self.omega_pub.publish(data)

		self.w_pre = self.w_now
		self.time_old = self.time_now

	def start(self):
		rospy.spin()

if __name__ == '__main__':
	rospy.init_node("ros_dcmotor")
	task = motor()
	task.start()