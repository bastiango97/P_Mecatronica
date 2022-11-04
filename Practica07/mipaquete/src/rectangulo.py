#!/usr/bin/env python
# licencia
import rospy
from geometry_msgs.msg import Twist
import sys
 
 
def turtle_rectangle():
	rospy.init_node('turtlesim', anonymous=True)
	pub = rospy.Publisher('/turtle1/cmd_vel',Twist, queue_size=10)
	rate = rospy.Rate(1)
	vel = Twist()
	while not rospy.is_shutdown():
		for i in range(2):
			vel.linear.x = 2
			vel.linear.y = 0
			vel.linear.z = 0
			vel.angular.x = 0
			vel.angular.y = 0
			vel.angular.z = 0
			pub.publish(vel)
			rate.sleep()
		vel.linear.x = 0
		vel.linear.y = 0
		vel.linear.z = 0
		vel.angular.x = 0
		vel.angular.y = 0
		vel.angular.z = 1.570796
		pub.publish(vel)
		rate.sleep()
		vel.linear.x = 2
		vel.linear.y = 0
		vel.linear.z = 0
		vel.angular.x = 0
		vel.angular.y = 0
		vel.angular.z = 0
		pub.publish(vel)
		rate.sleep()
		vel.linear.x = 0
		vel.linear.y = 0
		vel.linear.z = 0
		vel.angular.x = 0
		vel.angular.y = 0
		vel.angular.z = 1.570796
		pub.publish(vel)
		rate.sleep()
		
if __name__ == '__main__':
    try:
        turtle_rectangle()
    except rospy.ROSInterruptException:
        pass
