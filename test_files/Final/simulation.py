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
## AUTHORS: Subham Sahoo, Nischay Nirajit Mahanta
##
################################################################################

import threading
import time
import sys


check=1
change=""
f1=[
[1,1,1,1,1,1,1,1],
[1,1,1,1,1,1,1,1],
[0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0],
[1,1,1,1,1,1,1,1],
[1,1,1,1,1,1,1,1]]
temp=[
[1,1,1,1,1,1,1,1],
[1,1,1,1,1,1,1,1],
[0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0],
[1,1,1,1,1,1,1,1],
[1,1,1,1,1,1,1,1]]
myrow=int()
mycol=int()
def child():
    global f1,myrow,mycol,check
    dict={'a':0,'b':1,'c':2,'d':3,'e':4,'f':5,'g':6,'h':7}
    while 1:
        input_str=raw_input('enter the initial move position : ')
	if (input_str=="ok"):
		check=1
		sys.exit()


        l=list(input_str);

        l2=dict[l[0]]
        l1=8-int(l[1])
        f1[l1][l2]=1-f1[l1][l2];
	myrow=l1
	mycol=l2


def main1():
    global f1,temp,myrow,mycol
    global change;
    out_put=""

    while 1:
        print(change)
	if check==1:
		break
        out_put=check(temp)
        if(out_put!=""):
	    if change =="" :
            	change=change+out_put
	    else:
		change=change+","+out_put
            out_put=""
            temp[myrow][mycol]=1-temp[myrow][mycol]
        time.sleep(.1)

def check(b):
    dict={0:'a',1:'b',2:'c',3:'d',4:'e',5:'f',6:'g',7:'h'}
    change2=""
    letter=str()
    row=int()
    col=int()
    val1=int()
    val2=int()
    if(f1==b):
        pass
    else:
        for i in range(0,8):
            if(f1[i]!=b[i]):
                for j in range (0,8):
                    if(f1[i][j]!=b[i][j]):
                        val1=f1[i][j]
                        val2=b[i][j]
                        row=8-i;
                        col=j;
        letter=dict[col]
        change2=letter+str(row)+" "+str(val2)+str(val1)

    return change2


trd=threading.Thread(target=child)
trd.daemon=True
trd.start()


main1()
