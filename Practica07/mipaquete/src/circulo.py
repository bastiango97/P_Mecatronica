#!/usr/bin/env python
# licencia
import rospy
from geometry_msgs.msg import Twist
import sys
 
 
def turtle_circle(radius):
    rospy.init_node('turtlesim', anonymous=True)
    pub = rospy.Publisher('/turtle1/cmd_vel',
                          Twist, queue_size=10)
    rate = rospy.Rate(10)
    vel = Twist()
    while not rospy.is_shutdown():
        vel.linear.x = radius
        vel.linear.y = 0
        vel.linear.z = 0
        vel.angular.x = 0
        vel.angular.y = 0
        vel.angular.z = 1
        rospy.loginfo("Radius = %f",
                      radius)
        pub.publish(vel)
        rate.sleep()
 
 
if __name__ == '__main__':
    try:
        turtle_circle(float(sys.argv[1]))
    except rospy.ROSInterruptException:
        pass
