#!/usr/bin/env python
import rospy
import chess
import chess.uci
import time
from std_msgs.msg import Int32,String,Bool
from chess_bot.msg import ui_data

eng=chess.uci.popen_engine("stockfish")
brd=chess.Board()
dict1={'a':0,'b':1,'c':2,'d':3,'e':4,'f':5,'g':6,'h':7}
indata="" #input UCI string decoded
outdata="" #output UCI string from stockfish too be encoded
master=False #master falg for the game logic
turn=False #False for user and True for stockfish
value=1 #global move type determinant
respn="#" #respawn character
cur_fen="" #to store fen
illigal=True #for detecting illigal moves
rwait=True #flag for system to stall during stockfish respawn

def diff(s):
    global value,dict1,brd
    reil=''
    value=len(s)
    if value==2: #normal move #promotion
        a=s[0]
        b=s[1]
	row=int(a[1])-1
	col=dict1[a[0]]
	index=8*row+col
	piece=str(brd.piece_at(index))
        if a[0]+a[1]!=b[0]+b[1] and (a[1]=="7" ) and ( b[1]=="8") and (piece=='P' or piece=='p'):
            reil=a[0]+a[1]+b[0]+b[1]
	    value=5
        elif a[0]+a[1]!=b[0]+b[1] and (a[1]=="2" ) and ( b[1]=="1") and (piece=='P' or piece=='p'):
            reil=a[0]+a[1]+b[0]+b[1]
	    value=5
        elif a[0]+a[1]!=b[0]+b[1]:
            reil=a[0]+a[1]+b[0]+b[1]
    elif value==3: #normal kill #en-passant kill
        a=s[0]
        b=s[1]
        c=s[2]
	row=int(b[1])-1
	col=dict1[b[0]]
	index=8*row+col
	piece=str(brd.piece_at(index))
        gen_str=a[3]+a[4]+b[3]+b[4]+c[3]+c[4]
	if gen_str=="101001" and (((b[1]=="7" ) and ( c[1]=="8")) or ((b[1]=="2" ) and ( c[1]=="1"))) and (piece=='P' or piece=='p'):
            reil=b[0]+b[1]+c[0]+c[1]
	    value=5
        elif gen_str=="101001":
            reil=b[0]+b[1]+c[0]+c[1]
        elif gen_str=="100110":
            reil=a[0]+a[1]+b[0]+b[1]
    elif value==4: #castling
        a=s[0]
        b=s[1]
        reil=a[0]+a[1]+b[0]+b[1]
    if(reil==''):
        print("Blank String Generated Redo the Move")
    return reil

#arduino steps generation
dict={'a':0,'b':1,'c':2,'d':3,'e':4,'f':5,'g':6,'h':7}
def arduino_steps(string,flag):
        ret_string=""

        irow_8=8-int(string[1])
        icol_8=dict[string[0]]
        frow_8=8-int(string[3])
        fcol_8=dict[string[2]]
        irow_16=irow_8*2+1
        icol_16=icol_8*2+1
        frow_16=frow_8*2+1
        fcol_16=fcol_8*2+1

        r_diff=frow_16 - irow_16
        c_diff=fcol_16 - icol_16
        if flag==0:
                ret_string+=normal_move(irow_16 - 7,icol_16 - 7);
                ret_string+=",1,"
                ret_string+= normal_move(r_diff,c_diff);
                ret_string+=",0,"
                ret_string+=normal_move(7-frow_16,7-fcol_16)

        if flag==1:
                a=0
                b=0
                check_kill=-1
                check_kill1=-1
                check_kill2=-1
                ret_string+=normal_move(frow_16-7,fcol_16-7)+",1,"
                a,b=killing_move(frow_16,fcol_16)
                ret_string+=normal_move(a,b)+",0,"+normal_move( -1*(a+r_diff), -1*(b+c_diff) )+",1,"+normal_move(r_diff,c_diff)+",0,"+normal_move(7-frow_16,7-fcol_16)
        if flag==2:
                ret_string+=normal_move(irow_16-7,fcol_16-7)+",1,"
                a,b=killing_move(irow_16,fcol_16)

                ret_string+=normal_move(a,b)+",0,"+normal_move( -1*(a), -1*(b+c_diff) )+",1,"+normal_move(r_diff,c_diff)+",0,"+normal_move(7-frow_16,7-fcol_16)

        if flag==3:
                ret_string+=normal_move(irow_16-7,icol_16-7)+",1,"
                if(fcol_8>icol_8):
                        ret_string+="x_4_1,0,x_2_1,1,"+normal_move(0,-4)+",0,"+normal_move(7-frow_16,5-icol_16)
                else:
                        ret_string+="x_4_0,0,x_4_0,1,"+normal_move(0,6)+",0,"+normal_move(7-frow_16,9-icol_16)
	ret_string=ret_string.replace('_','')
        ret_string=ret_string.replace(',1,','H')
        ret_string=ret_string.replace(',0,','L')
        ret_string=ret_string.replace(',','')
        return ret_string

def normal_move(r_diff,c_diff):
        ret_string=""
        check_row=-1
        check_col=-1
        if r_diff<=0:
                ret_string+="y_1_1"
                check_row=0
        else:
                ret_string+="y_1_0"
                check_row=1
        if r_diff==0:
                check_row=1

        if c_diff<0:
                ret_string+=",x_"+str( abs(c_diff)-1)+"_0"
                check_col=0

        elif c_diff>0:
                ret_string+=",x_"+str(c_diff-1)+"_1"
                check_col=1
        elif c_diff==0:
                ret_string+=",x_1_0"
                check_col=1
        else :
                pass

        if r_diff>0:
                ret_string+=",y_"+str(r_diff)+"_0"
        elif r_diff<0:
                ret_string+=",y_"+str(abs(r_diff))+"_1"
        elif r_diff==0:
                ret_string+=",y_2_0"
        else:
                pass
        ret_string+=",x_1_"+str(check_col)+",y_1_"+str(check_row)


        return ret_string;

def killing_move(frow_16,fcol_16):
        t_row=15-frow_16   #to throw the piece nearest col
        t_col=15-fcol_16   #to throw the piece nearest row
        if(t_row>7):
                t_row=15-t_row
                check_kill1=0
        else:
                check_kill1=2

        if(t_col>7):
                t_col=15-t_col
                check_kill2=1
        else:
                check_kill2=3

        if(t_row>t_col):
                check_kill=check_kill2
        else:
                check_kill=check_kill1
        if(check_kill==0):
                a=-2-frow_16
                b=0
                #ret_string+=normal_move(-2-frow_16,0)+",0,"+normal_move()
        elif (check_kill==1):
                a=0
                b=-2-fcol_16
        elif (check_kill==2):
                a=17-frow_16
                b=0
        elif (check_kill==3):
                a=0
                b=17-fcol_16
        return a,b
#end arduino steps generation

def checking_(string_):
	global brd
	flag=99
    	if(brd.is_capture(string_)):
        	flag=1
    	if(brd.is_en_passant(string_)):
        	flag=2
    	if(brd.is_castling(string_)):
        	flag=3
    	if(flag==99):
        	flag=0
    	return flag

def decode(mv):
	global indata,master
	indata=diff(mv.data.split(','))
    	if(indata!=''):
		master=True

def uicall(uidat):
	global turn,respn,illigal,master,rwait
	if uidat.type==0:
		if uidat.sys!="yes":
			turn=True
			master=True
	elif uidat.type==1:
		rwait=False
	elif uidat.type==2:
		respn=uidat.sys
	elif uidat.type==3:
		illigal=False

def main_():
	global master,turn,indata,cur_fen,respn,illigal,value,outdata,rwait,eng,brd
	rospy.init_node('chess_ai')
	flagpub = rospy.Publisher('turn_flag', Bool, queue_size=10)
	uipub = rospy.Publisher('ui_send', ui_data, queue_size=10)
	fenpub = rospy.Publisher('fendata', String, queue_size=10)
	ardpub = rospy.Publisher('move_seq', String, queue_size=10)
	rospy.Subscriber('board_string', String, decode)
	rospy.Subscriber('ui_recv', ui_data, uicall)

	#this occurs for the first time the game starts
	time.sleep(5)
	temp=ui_data()
	temp.type=0
	temp.sys="Enter 'yes' to move first \nand press select"
	uipub.publish(temp)

	rate = rospy.Rate(20)
	while not rospy.is_shutdown():
		if master==True:
			flagpub.publish(turn)
			if turn==False: #user turn
                		print('user turn')
				print(indata)
				if value==5: #for respawn move
					temp.type=2
					temp.sys="Enter the respawn character \nand press select"
					uipub.publish(temp)
					while respn=="#":
						time.sleep(0.01)
					indata=indata+respn
					respn="#"
				if chess.Move.from_uci(indata) in brd.legal_moves: #for legal move
					print('correct move')
					brd.push(chess.Move.from_uci(indata))
					temp.type=4
					temp.mo=indata
					uipub.publish(temp)
					if brd.is_stalemate():
						temp.type=5
						temp.sys="Game Over its a draw please \nrestart the game to play again"
						uipub.publish(temp)
						eng.quit()
					if brd.is_checkmate():
						temp.type=5
						temp.sys="Game over congratulations you won please \nrestart the game to play again"
						uipub.publish(temp)
						eng.quit()
					turn=True
				else: #for illigal move
					print('incorrect move')
					temp.type=3
					temp.sys="Illigal Move please correct the \nmove and press select"
					uipub.publish(temp)
					turn=True
					flagpub.publish(turn)
					while illigal==True:
						time.sleep(0.01)
					illigal=True
					turn=False
			elif turn==True: #stockfish turn
				print('stockfish turn')
				eng.position(brd)
				bst,pon=eng.go(movetime=30)
				move_flag=checking_(bst)
				brd.push(bst)
				outdata=bst.uci()
                		print(outdata)
				temp.type=4
				temp.mo=outdata
				uipub.publish(temp)
				yes_respn=False
				if len(outdata)==5:
					yes_respn=True
					temp.type=1
					temp.sys="Please replace "+outdata[2]+outdata[3]+" with "+outdata[4]+"\n and press select"
					uipub.publish(temp)
					outdata=outdata[0:4]
				###
				strsend=str()
				mystr=arduino_steps(outdata,move_flag)
				strsend="1_"+mystr[0:50];
				ardpub.publish(strsend)
				time.sleep(0.5)
				if(len(mystr)>50):
					strsend="2_"+mystr[50:len(mystr)]
					ardpub.publish(strsend)
					time.sleep(0.5)
				strsend="ok"
				ardpub.publish(strsend)
				###
				if yes_respn==True:
					while rwait==True:
						time.sleep(0.01)
					rwait=True
				if brd.is_stalemate():
					temp.type=5
					temp.sys="Game Over its a draw please \nrestart the game to play again"
					uipub.publish(temp)
					eng.quit()
				if brd.is_checkmate():
					temp.type=5
					temp.sys="Game Over Stockfish won please \nrestart the game to play again"
					uipub.publish(temp)
					eng.quit()
				turn=False
			fenpub.publish(brd.fen())
		if turn==False:
			master=False
		rate.sleep()

if __name__ == '__main__':
    try:
        main_()
    except rospy.ROSInterruptException:
        pass
