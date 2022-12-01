import time
import rospy
from std_msgs.msg import Float64
from std_msgs.msg import Duration

# class mtor(object):
# 	def __init__(self):
	
# 		self.time_old = time.time()
# 		self.time_now = time.time()

# 		self.looprate = rospy.Rate(1000)

# 		rospy.Subscriber('/voltage',Float64,self.cb_voltage)

# 		self.omega_pub = rospy.Publisher("/omega",Float64,queue_size=1)

# 	def cb_voltage(self,msg):
# 		self.voltage = msg.data

# 	def start(self):
# 		while not rospy.is_shutdown():

# 			self.time_now = time.time()
# 			Ts = (self.time_now - self.time_old)

# 			print(Ts)

# 			self.time_old = self.time_now

# 			self.looprate.sleep()

# if __name__ == '__main__':
# 	rospy.init_node("ros_dcmotor")
# 	oo = mtor()
# 	oo.start()


# rospy.sleep(rospy.Duration(1.5))
# time_end = rospy.Time.now()
# duration = time_end - time_begin
# rospy.loginfo("Slept for " + str(duration.to_sec()) + " secs")


rospy.init_node("test_duration")

# time_begin = rospy.Time.now()
time_begin = time.time()

duration = rospy.Duration(100)

rate = rospy.Rate(duration.to_sec())
duration_publisher = rospy.Publisher("/duration", Float64, queue_size=1)

while not rospy.is_shutdown():
	# time_end = rospy.Time.now()
	time_end = time.time()
	duration_diff = Float64()
	duration_diff.data = time_end - time_begin
	duration_publisher.publish(duration_diff)
	time_begin = time_end
	rate.sleep()