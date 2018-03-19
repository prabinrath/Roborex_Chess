#!/usr/bin/env python
import rospy
from std_msgs.msg import String
from time import sleep

def send_debug():

    rospy.init_node('send_debug')
    pub = rospy.Publisher('move_seq', String, queue_size=1000)
    while not rospy.is_shutdown():
	pub.publish("ok")
	sleep(0.2);

if __name__ == '__main__':
    send_debug()
