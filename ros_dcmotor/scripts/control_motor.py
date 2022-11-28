#!/usr/bin/env python
import rospy
from std_msgs.msg import Float64

class motor(object):
	def __init__(self):
		self.a = 27
		self.b = 17

		self.time_old = rospy.Time.now().to_sec()
		self.time_now = rospy.Time.now().to_sec()

		self.w_d = 0
		self.w_act = 0
		self.voltage = 0

		rospy.Subscriber('/omega_desired',Float64,self.omega_cb)            # subscribe to voltage
		self.omega_pub = rospy.Publisher("/voltage",Float64,queue_size=1) # publish rotation speed

	def omega_cb(self,msg):

		self.w_d = msg.data

		self.time_now = rospy.Time.now().to_sec()

		Ts = (self.time_now - self.time_old)

		term_1 = 2 # PI
		term_2 = (1/self.b)*w # FF
		term_3 = 2 # FF

		self.control_voltage = term_1 + term_2 + term_3
		
		data = Float64()
		data.data = self.control_voltage
		self.omega_pub.publish(control_voltage)

		self.w_pre = self.w_now
		self.time_old = self.time_now

	def start(self):
		rospy.spin()

if __name__ == '__main__':
	rospy.init_node("ros_dcmotor_control")
	task = motor()
	task.start()