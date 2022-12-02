#! /usr/bin/env python
import rospy
from std_msgs.msg import Float32
from ros_dcmotor.msg import motor

class motor_control(object):
	def __init__(self):

		# Motor Parameter
		self.a = 27.65
		self.b = 17.35
		self.c = 5.635
		self.PPR = 23
		self.GR = 13

		# PID
		self.pi = 3.141592653
		self.wn = 2*self.pi*6
		self.zeta = 1
		self.kp = (2*self.zeta*self.wn - self.a)/self.b
		self.ki = (self.wn**2)/self.b
		
		# variable
		self.time_old = rospy.Time.now().to_sec()
		self.time_now = rospy.Time.now().to_sec()

		self.input = 0
		self.cumError = 0
		self.omega_desired_old = 0
		self.omega_desired_now = 0
		self.theta_old = 0
		self.theta_now = 0
		self.Ts = 0.0001

		self.looprate = rospy.Rate(100)

		self.voltage_pub = rospy.Publisher("/right_cmd",Float32,queue_size=1)
		rospy.Subscriber('/motor_right',motor,self.update_theta)
		rospy.Subscriber('/motor_right_desired',Float32,self.update_w_desired)

	def update_theta(self,msg):
		self.time_now = msg.header.stamp.to_sec()
		self.theta_now = (2*self.pi*msg.encoder)/(self.PPR*self.GR)

	def update_w_desired(self,msg):
		self.omega_desired_now = msg.data()

  	def start(self):
  		while not rospy.is_shutdown():
  			# calculate time step
			self.Ts = self.time_now - self.time_old

			# calculate omega now
			omega_now = (self.theta_now - self.theta_old)/self.Ts

			# control
			error = self.omega_desired_now - omega_now
			self.input = (self.kp * error) + (self.ki * (self.cumError + error * self.Ts)) + ((self.a / self.b) * self.omega_desired_now) + ((1 / self.b) * ((self.omega_desired_now - self.omega_desired_old) / self.Ts))

			# Limit voltage
			if self.input > 23.5:
				self.input = 23.5
			elif self.input < -23.5:
				self.input = -23.5
			
			# publish input voltage to motor
			vol = Float32()
			vol.data = self.input
			self.voltage_pub.publish(vol)

			# update old time step to new time step
			self.time_old = self.time_now
			self.cumError += error * self.Ts
			self.omega_desired_old = self.omega_desired_now
			
			# loop ROS
			self.looprate.sleep()

if __name__ == '__main__':
	rospy.init_node("motor_velo_controller")
	mc = motor_control()
	mc.start()