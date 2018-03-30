#!/usr/bin/env python

################################################################################
##
## MIT License
##
## Copyright (c) 2018 Team Roborex, NIT Rourkela
##
## Permission is hereby granted, free of charge, to any person obtaining a copy
## of this software and associated documentation files (the "Software"), to deal
## in the Software without restriction, including without limitation the rights
## to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
## copies of the Software, and to permit persons to whom the Software is
## furnished to do so, subject to the following conditions:
##
## The above copyright notice and this permission notice shall be included in all
## copies or substantial portions of the Software.
##
## THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
## IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
## FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
## AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
## LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
## OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
## SOFTWARE.
##
################################################################################
################################################################################
##
## AUTHORS: Prabin Rath
##
################################################################################

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
