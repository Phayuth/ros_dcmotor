import time
import rospy
from std_msgs.msg import Float64

class mtor(object):
	def __init__(self):
	
		self.time_old = time.time()
		self.time_now = time.time()

		self.looprate = rospy.Rate(1000)

		rospy.Subscriber('/voltage',Float64,self.cb_voltage)

		self.omega_pub = rospy.Publisher("/omega",Float64,queue_size=1)

	def cb_voltage(self,msg):
		self.voltage = msg.data

	def start(self):
		while not rospy.is_shutdown():

			self.time_now = time.time()
			Ts = (self.time_now - self.time_old)

			print(Ts)

			self.time_old = self.time_now

			self.looprate.sleep()

if __name__ == '__main__':
	rospy.init_node("ros_dcmotor")
	oo = mtor()
	oo.start()