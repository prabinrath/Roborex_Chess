#!/usr/bin/env python
import rospy
from std_msgs.msg import String

filter_flag=False

def callback(data):
    if data.data=='ok' and filter_flag==False:
	print(data.data)
	filter_flag=True;
    if data.dat!='ok':
	

def debug_ardu():
    rospy.init_node('debug_ardu')
    rospy.Subscriber('user_swh', String, callback)
    rospy.spin()

if __name__ == '__main__':
    debug_ardu()
