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
		

		self.cumError = 0
		self.omega_desired_old = 0
		self.omega_desired_now = 0
		self.omega_now = 0
		self.Ts = 0.01

		self.looprate = rospy.Rate(100)

		self.voltage_pub = rospy.Publisher("/right_cmd",Float32,queue_size=1)
		rospy.Subscriber('/omega',motor,self.update_omega)
		rospy.Subscriber('/motor_right_desired',Float32,self.update_w_desired)
		timer = rospy.Timer(rospy.Duration(0.01),self.start)
		rospy.spin()

	def update_omega(self,msg):
		# self.time_now = msg.header.stamp.to_sec()
		self.omega_now = msg.speed

	def update_w_desired(self,msg):
		self.omega_desired_now = msg.data

  	def start(self,event):
  		time_now = rospy.Time.now().to_sec()
  		self.Ts = time_now - self.time_old
		print(self.Ts)
		# control
		error = self.omega_desired_now - self.omega_now
		# print(error)
		input_vol = (self.kp * error) + (self.ki * (self.cumError + error * self.Ts)) + ((self.a / self.b) * self.omega_desired_now) + ((1 / self.b) * ((self.omega_desired_now - self.omega_desired_old) / self.Ts))
		# print(input_vol)
		# Limit voltage
		if input_vol > 23.5:
			input_vol = 23.5
		elif input_vol < -23.5:
			input_vol = -23.5
		
		# publish input voltage to motor
		vol = Float32()
		vol.data = input_vol
		self.voltage_pub.publish(vol)

		# update old time step to new time step
		self.time_old = time_now
		self.cumError += error * self.Ts
		self.omega_desired_old = self.omega_desired_now

if __name__ == '__main__':
	rospy.init_node("motor_velo_controller")
	mc = motor_control()