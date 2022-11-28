#! /usr/bin/env python
import rospy
from std_msgs.msg import Float64

class motor_control(object):
	def __init__(self):

		# Motor Parameter
		self.a = 27.65
		self.b = 17.35
		self.c = 5.635

		# PID
		self.pi = 3.141592653
		self.wn = 2*self.pi*6
		self.zeta = 1
		self.kp = (2*self.zeta*self.wn - self.a)/self.b
		self.ki = (self.wn**2)/self.b
		
		# variable
		self.Ts_old = rospy.Time.now().to_sec()
		self.Ts_new = rospy.Time.now().to_sec()

		self.input = 0
		self.cumError = 0
		self.omega_desired_prev = 0
		self.omega_current = 0
		self.Ts = 0.0001

		self.looprate = rospy.Rate(100)

		self.voltage_pub = rospy.Publisher("/voltage",Float64,queue_size=1)
		rospy.Subscriber('/omega',Float64,self.callb_right)

	def callb_right(self,msg):
		self.omega_current = msg.data

  	def start(self):
  		while not rospy.is_shutdown():
  			# calculate time step
			self.Ts_new = rospy.Time.now().to_sec()
			self.Ts = self.Ts_new - self.Ts_old

			# control
			wrd = 11.5
			error = wrd - self.omega_current
			self.input = (self.kp * error) + (self.ki * (self.cumError + error * self.Ts)) + ((self.a / self.b) * wrd) + ((1 / self.b) * ((wrd - self.omega_desired_prev) / self.Ts))

			# publish input voltage to motor
			vol = Float64()
			vol.data = self.input
			self.voltage_pub.publish(vol)

			# update old time step to new time step
			self.Ts_old = self.Ts_new
			self.cumError += error * self.Ts
			self.omega_desired_prev = wrd
			
			# loop ROS
			self.looprate.sleep()

if __name__ == '__main__':
	rospy.init_node("motor_velo_controller")
	mc = motor_control()
	mc.start()