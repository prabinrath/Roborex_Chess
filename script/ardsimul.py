#!/usr/bin/env python
import rospy
import threading
from std_msgs.msg import String
from time import sleep

a=''

def child():
	global master,toggl,a
	while(1):
		a=raw_input("Enter turn state: ")

def ardsimul():
	global li,toggl,master,a
	rospy.init_node('ardsimul')
	pub = rospy.Publisher('user_swh', String, queue_size=1000)
	trd=threading.Thread(target=child)
	trd.daemon=True
	trd.start()

	rate = rospy.Rate(20)
	while not rospy.is_shutdown():
		send=String()
		if a=='ok' or a=='n':
			send.data=a
			pub.publish(send)
			a=''
		rate.sleep()

if __name__ == '__main__':
    try:
        ardsimul()
    except rospy.ROSInterruptException:
        pass
