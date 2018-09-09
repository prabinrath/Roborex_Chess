dict1={'a':0,'b':1,'c':2,'d':3,'e':4,'f':5,'g':6,'h':7};

def arduino_steps(string,flag):

        ret_string=""

        irow_8=8-int(string[1])
        icol_8=dict1[string[0]]
        frow_8=8-int(string[3])
        fcol_8=dict1[string[2]]
        irow_16=irow_8*2+1
        icol_16=icol_8*2+1
        frow_16=frow_8*2+1
        fcol_16=fcol_8*2+1

        r_diff=frow_16 - irow_16
        c_diff=fcol_16 - icol_16
        if flag==0:  #normal move
                ret_string+=normal_move(irow_16 - 7,icol_16 - 7);
                ret_string+=",1,"
                ret_string+= normal_move(r_diff,c_diff);
                ret_string+=",0,"
                ret_string+=normal_move(7-frow_16,7-fcol_16)

        if flag==1:  #killing move
                a=0
                b=0
                check_kill=-1
                check_kill1=-1
                check_kill2=-1
                ret_string+=normal_move(frow_16-7,fcol_16-7)+",1,"
                a,b=killing_move(frow_16,fcol_16)
                ret_string+=normal_move(a,b)+",0,"+normal_move( -1*(a+r_diff), -1*(b+c_diff) )+",1,"+normal_move(r_diff,c_diff)+",0,"+normal_move(7-frow_16,7-fcol_16)
        if flag==2:  #en passant
                ret_string+=normal_move(irow_16-7,fcol_16-7)+",1,"
                a,b=killing_move(irow_16,fcol_16)

                ret_string+=normal_move(a,b)+",0,"+normal_move( -1*(a), -1*(b+c_diff) )+",1,"+normal_move(r_diff,c_diff)+",0,"+normal_move(7-frow_16,7-fcol_16)

        if flag==3: #casling move
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
        if(r_diff==0):
                ret_string+="y_1_1"
                if(c_diff>0):
                        ret_string+=",x_"+str(c_diff)+"_1"
                else:
                        ret_string+=",x"+str(abs(c_diff))+"_0"
                ret_string+=",y_1_0";
        elif(c_diff==0):
                ret_string+="x_1_0"
                if(r_diff>0):
                        ret_string+=",y_"+str(r_diff)+"_0"
                else:
                        ret_string+=",y_"+str(abs(r_diff))+"_1"
                ret_string+="x_1_1"
        else:
                if(r_diff>0 and c_diff>0):
                        ret_string+="y_1_0"+",x_"+str(c_diff-1)+"_1"+",y_"+str(r_diff-1)+"_0"+",x_1_1"
                elif(r_diff>0 and c_diff<0):
                        ret_string+="y_1_0"+",x_"+str(abs(c_diff)-1)+"_0"+",y_"+str(r_diff-1)+"_0"+",x_1_0"
                elif(r_diff<0 and c_diff>0):
                        ret_string+="y_1_1"+",x_"+str(c_diff-1)+"_1"+",y_"+str(abs(r_diff)-1)+"_1"+",x_1_1"
                elif(r_diff<0 and c_diff<0):
                        ret_string+="y_1_1"+",x_"+str(abs(c_diff)-1)+"_0"+",y_"+str(abs(r_diff)-1)+"_1"+",x_1_0"
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
                a=-1-frow_16
                b=0
                #ret_string+=normal_move(-2-frow_16,0)+",0,"+normal_move()
        elif (check_kill==1):
                a=0
                b=-1-fcol_16
        elif (check_kill==2):
                a=17-frow_16
                b=0
        elif (check_kill==3):
                a=0
                b=17-fcol_16
        return a,b
#end arduino steps generation



def main():

        string1=raw_input("enter move to determine steps\n")
        flag=int(raw_input("enter flag "))
        final_string=arduino_steps(string1,flag)
        print final_string

main()
