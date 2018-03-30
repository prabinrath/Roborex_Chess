'''
It takes the inputs from the simulation as string
and finds out the string that is to be pushed
in the stockfish

'''
dot_string=raw_input("Enter The string ")

cart_list=[]
cart_list=dot_string.split(',')
#print(cart_list)
dot=len(cart_list)
def call_boy(dot):
    if dot==2:
        make=1
    if dot==3:
        make=2
    if dot==4:
        make=3
    return (make)
    '''
def promoted:
    promoted_piece=raw_input("enter the promoted piece as entered in ui")
'''

def diff(s):
    value=call_boy(dot)
    if value==1: # Normal move # ponder move ###################promotion
        a=s[0]
        b=s[1]
        print(a,b)
        gen_str=a[3]+a[4]+b[3]+b[4]
        if  a[0]+a[1]==b[0]+b[1]:
            print("ponder move ")
            print("don't send any command to chess engine")
        elif a[0]+a[1]!=b[0]+b[1] and (a[1]=="7" ) and ( b[1]=="8"):
            print("promotion move call function specified")
            #The_promoted_piece=promoted()
            reil=a[0]+a[1]+b[0]+b[1]+The_promoted_piece
        elif a[0]+a[1]!=b[0]+b[1] and (a[1]=="2" ) and ( b[1]=="1"):
            print("promotion move call function specified")
            The_promoted_piece=promoted()
            reil=a[0]+a[1]+b[0]+b[1]+The_promoted_piece.upper()
        elif a[0]+a[1]!=b[0]+b[1]:
            print("normal move ")
            reil=a[0]+a[1]+b[0]+b[1]
            return reil

    elif value==2: # normal kill  #en passant kill
        a=s[0]
        b=s[1]
        c=s[2]
        print(a,b,c)
        gen_str=a[3]+a[4]+b[3]+b[4]+c[3]+c[4]
        if gen_str=="101001":
            print("normal kill")
            reil=b[0]+b[1]+c[0]+c[1]
        elif gen_str=="100110":
            print("enpassant kill")
            reil=a[0]+a[1]+b[0]+b[1]
        return reil
    elif value==3: #castling
        a=s[0]
        b=s[1]
        c=s[2]
        d=s[3]
        print(a,b,c,d)
        gen_str=a[0]+a[1]+b[0]+b[1]
        print("castling")
        return gen_str
kl=diff(cart_list)
print("THe move is  ",kl)
