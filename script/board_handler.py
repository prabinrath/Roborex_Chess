#!/usr/bin/env python
import rospy
from std_msgs.msg import String

checko=False #flag to send the encoded string to chess_ai & to track the turn-switch state from arduino
append_flag=True #flag to allow the stock fish move get updated with f1

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

def decode_rows(s):
	s=s.split(',')
	i=0
	while i<8:
		if (i%2==0):
			s[i]=list(s[i])
			s[i].reverse()
		else:
			s[i]=list(s[i])
			for j in range(0,8,2):
				s[i][j],s[i][j+1]=s[i][j+1],s[i][j]
		i=i+1
	j=0
	for j in range(1,9,2):
		s[j].reverse()
	i=0
	while i<4:
		s[i],s[7-i]=s[7-i],s[i]
		i=i+1
	q=""
	j=0
	while j<8:
		q=q+s[j][0]+s[j][1]+s[j][2]+s[j][3]+s[j][4]+s[j][5]+s[j][6]+s[j][7]
		if (j<7):
			q=q+','
		j=j+1 
	return q

def final_string_produce():
	global change
	a=change
	a=change.split("-")
	final_string=str()
	for i in a:
		if(len(i)==5):
			final_string+=","+i
		elif(len(i)==11):
			k=i.split(",")
			if len(change)==23:
				if 'g' in i and 'h' in i :
					final_string+=","+k[0]+","+k[1]
				elif 'a' in i and 'c' in i :
					final_string+=","+k[1]+","+k[0]
				elif 'e' in i and 'g' in i :
					final_string+=","+k[0]+","+k[1]
				elif 'h' in i and 'f' in i :
					final_string+=","+k[1]+","+k[0]
				elif 'e' in i and 'c' in i :
					final_string+=","+k[1]+","+k[0]
				elif 'a' in i and 'd' in i :
					final_string+=","+k[0]+","+k[1]
			elif len(change)==17 and change[0:2]!=change[6:8] and change[6:8]!=change[12:14] and change[0:2]!=change[12:14]:
				if k[0][1]=='4':
					final_string=","+k[0]+","+k[1]+final_string		
				elif k[1][1]=='5':
					final_string=","+k[1]+","+k[0]+final_string		

			else:
				if k[0][3]=='1' and k[0][4]=='0':
					final_string+=","+k[0]+","+k[1]
				else:
					final_string+=","+k[1]+","+k[0]
			
		elif(len(i)==17):
			if(len(change)==17):
				pp=i.split(',')
				if(change.count('4')==2 and change.count('3')==1):
					if(pp[0][1]=='4' and pp[1][1]=='4' and pp[2][0]==pp[0][0]):
						final_string+=","+pp[1]+","+pp[2]+","+pp[0]
					elif(pp[0][1]=='4' and pp[1][1]=='4' and pp[2][0]==pp[1][0]):
						final_string+=","+pp[0]+","+pp[2]+","+pp[1]
				elif(change.count('5')==2 and change.count('6')==1):
					if(pp[1][1]=='5' and pp[2][1]=='5' and pp[0][0]==pp[1][0]):
						final_string+=","+pp[2]+","+pp[0]+","+pp[1]
					elif(pp[1][1]=='5' and pp[2][1]=='5' and pp[0][0]==pp[2][0]):
						final_string+=","+pp[1]+","+pp[0]+","+pp[2]
			elif(len(change)==23):
				pp=i.split(",") 
				if('e' in i and 'g' in  i and 'h' in i ):
					final_string+=","+pp[0]+","+pp[1]+","+pp[2]
				elif('f' in i and 'g' in  i and 'h' in i):
					final_string+=","+pp[1]+","+pp[2]+","+pp[0]
				elif('e' in i and 'c' in  i and 'a' in i):
					final_string+=","+pp[2]+","+pp[1]+","+pp[0]
				elif('a' in i and 'c' in  i and 'd' in i):
					final_string+=","+pp[1]+","+pp[0]+","+pp[2]
					
		elif(len(i)==23):
			k=i.split(",")
			s1=str()
			s2=str()
			s3=str()
			s4=str()
			if('e' in i and 'a' in i and 'c' in i and 'd' in i):
				for y in k:
					if 'e' in y:
						s1=y
					elif 'c' in y:
						s2=y
					elif 'a' in y:
						s3=y
					elif 'd' in y:
						s4=y
			elif('e' in i and 'f' in i and 'g' in i and 'h' in i):
				for y in k:
					if 'e' in y:
						s1=y
					elif 'g' in y:
						s2=y
					elif 'h' in y:
						s3=y
					elif 'f' in y:
						s4=y
			final_string+=","+s1+","+s2+","+s3+","+s4	
	final_string=final_string[1:len(final_string)]
	return final_string

def check(b):
    global f1
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
			f1[i][j]=b[i][j]
			if change2=="":
		        	change2=letter+str(row)+" "+str(val1)+str(val2)
			else:
				change2+=","+letter+str(row)+" "+str(val1)+str(val2)
    return change2

def switch_turn(swh):
	global checko,append_flag
	if swh.data=='ok':
		checko=True
		append_flag=True
	elif swh.data=='n':
		append_flag=False

def encode(bot):
	global checko,change,append_flag
	out_put=""
	if checko==False:
		temp=decode_rows(bot.data).split(',')
		#print(temp)
		for i in range(0,8):
			temp[i]=list(temp[i])
		for i in range(0,8):
			for j in range(0,8):
				temp[i][j]=int(temp[i][j])
		out_put=check(temp)
		if(out_put!="" and append_flag==False):
			if change =="" :
				change=change+out_put
			else:
				change=change+"-"+out_put
		#print change 
def main_():
	global change,checko
	rospy.init_node('board_handler')
	pub = rospy.Publisher('board_string', String, queue_size=10) #encoded string publication to chess_ai for UCI string decoding
	rospy.Subscriber('bot_data', String, encode) #binary matrix subscription for encoded string generation
	rospy.Subscriber('user_swh', String, switch_turn) #switch state data from arduino
	rate = rospy.Rate(40)
	while not rospy.is_shutdown():
		if checko == True:
			data_send=final_string_produce()
			print(change)
			print('final:'+data_send)
			print(f1)
			pub.publish(data_send)
			change=""
			checko=False
		rate.sleep()

if __name__ == '__main__':
    try:
        main_()
    except rospy.ROSInterruptException:
        pass
