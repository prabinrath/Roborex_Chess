#Test file for Roborex Chess game features simulation
'''
******************                  TAB_WIDTH=8
README:The following code is just for testing the game features. Dont check for the robustness of the code. The program terminates for unusual exceptions which is supposed to be handled during insertion of the code into the final ROS node.
Change the saving directory accordingly before running.
'''

import os
import chess
import chess.pgn
import chess.uci
import time

flag=True
choice=0
eng=chess.uci.popen_engine("stockfish")
inp=''

############################################### Helping Functions #######################################################
def nth_retrival(event,white,black,round_):
    new_pgn=open("/home/prabin/chess/Final/gamedata.pgn")
    i=0
    for i,headers in chess.pgn.scan_headers(new_pgn):
        if(headers["Event"]==event) and (headers["White"]==white) and (headers["Black"]==black) and (headers["Round"]==round_):
            game=chess.pgn.read_game(new_pgn)
            game.headers["Event"]=headers["Event"]
            game.headers["White"]=headers["White"]
            game.headers["Black"]=headers["Black"]
            game.headers["Round"]=headers["Round"]
            game.headers["Date" ]=headers["Date" ]
            print('Found saved game')
            brd=game.board()
            for move in game.main_line():
                brd.push(move)
	    print(str(brd)+'\n')
    	    ret_data=[game,brd]
    	    return ret_data
    return 0

def nth_deletion(event,white,black,round_):
    new=open("/home/prabin/chess/Final/gamedata.pgn")
    i=0
    game_data=open("/home/prabin/chess/Final/tempo.pgn","w")
    for i,headers in chess.pgn.scan_headers(new):
        if(headers["Event"]==event) and (headers["White"]==white) and (headers["Black"]==black) and (headers["Round"]==round_):
            continue
        else:
            game=chess.pgn.read_game(new)
            game.headers["Event"]=headers["Event"]
            game.headers["White"]=headers["White"]
            game.headers["Black"]=headers["Black"]
            game.headers["Round"]=headers["Round"]
            game.headers["Date"]=headers["Date"]
            exporter=chess.pgn.FileExporter(game_data)
            game.accept(exporter)
    game_data.close()
    os.remove("/home/prabin/chess/Final/gamedata.pgn")
    os.rename("/home/prabin/chess/Final/tempo.pgn","/home/prabin/chess/Final/gamedata.pgn")

def logger(game,string):
	log=open("/home/prabin/chess/Final/log.txt","a")
	log.write(game.headers["Event"]+','+game.headers["White"]+','+game.headers["Black"]+','+game.headers["Round"]+','+time.ctime()+','+string+'\n')
	log.close()

def kyle():
    	current_time=time.ctime()
    	parser={'Jan':'01','Feb':'02','Mar':'03','Apr':'04','May':'05','Jun':'06','Jul':'07','Aug':'08','Sep':'09','Oct':'10','Nov':'11','Dec':'12'}
    	ll=current_time.split()
    	return ll[-1]+':'+parser[ll[1]]+':'+ll[2]

##########################################################################################################################

#Game initialization
if os.path.exists("/home/prabin/chess/Final/temp.pgn"): #add turn setup after recovery
	print("Previous game crashed\n")
	new_pgn=open("/home/prabin/chess/Final/temp.pgn")
        game=chess.pgn.read_game(new_pgn)
        node=game.end()
        brd=game.board()
        for move in game.main_line():
		brd.push(move)
	print(str(brd)+'\n')
    	logger(game,"Crashed Game")
    	'''
	if ' b ' in brd.fen(): 
		flag=False
	'''                  
else:
	print("\nRoborex Chess game features simulation\n")
	choice=input("\nEnter 1 for new game\nEnter 2 to load saved game\nEnter 3 to quit\n\n")
	if choice==1:
		print("New game\n")
		brd=chess.Board()
		game=chess.pgn.Game()
		game.headers["Event"]=raw_input("Enter game Event: ")
		game.headers["White"]=raw_input("Enter Player name for White: ")
		game.headers["Black"]=raw_input("Enter Player name for Black: ")
		game.headers["Round"]=raw_input("Enter Round number: ")
		game.headers["Date" ] =kyle()
		logger(game,"New game")
		if input('\nEnter 1 to have first move else any other number: ')==1:
			flag=True
		else:
			flag=False
	elif choice==2: #game quits for wrong load data inputs
		loaded=nth_retrival(raw_input("Enter game Event: "),raw_input("Enter Player name for White: "),raw_input("Enter Player name for Black: "),raw_input("Enter Round number: "))
		if loaded==0:
			choice=3
		else:
			game=loaded[0]
			node=game.end()
			logger(game,"retrived")
			brd=loaded[1]
	else:
		pass

#Infinite loop for game cycles
while(True and choice!=3):
	inp=''
	save_flag=False
	print('\nPossible inputs: move,undo,rst,save,quit')
	if flag==True: #user turn
		print("user turn")
		inp=raw_input('Enter your move: ')
		if inp=='save':
			if os.path.exists("/home/prabin/chess/Final/gamedata.pgn"): #checking the presence of a previously saved game with equal parameters
				pgn_=open("/home/prabin/chess/Final/gamedata.pgn")
				for i,headers in chess.pgn.scan_headers(pgn_):
					if(headers["Event"]==game.headers["Event"]) and (headers["White"]==game.headers["White"]) and (headers["Black"]==game.headers["Black"]) and (headers["Round"]==game.headers["Round"]):
						pgn_.close()
						nth_deletion(game.headers["Event"],game.headers["White"],game.headers["Black"],game.headers["Round"])
						break
				pgn_.close()
			pgn_=open("/home/prabin/chess/Final/gamedata.pgn","a")
			exporter = chess.pgn.FileExporter(pgn_)
			game.accept(exporter)
			pgn_.close()
			logger(game,'save')

		elif inp=='quit':
			eng.quit()
			logger(game,'quit')
			break
		elif inp=='undo':
			if len(game.variations)==1:
				node.parent.remove_variation(brd.pop())
				del node
				node=game.end()
				node.parent.remove_variation(brd.pop())
				del node
				node=game.end()
				print(brd)
				logger(game,'undo')
			else:
				print('Nothing To Undo!')
			
		elif inp=='rst':
			temp=chess.pgn.Game()
			temp.headers['Event']=game.headers['Event']
			temp.headers['White']=game.headers['White']
			temp.headers['Black']=game.headers['Black']
			temp.headers['Round']=str(int(game.headers['Round'])+1)
			temp.headers['Date']=kyle()
			game=temp
			brd=game.board()
			logger(game,'reset')
			print('Game Restart')
			print(brd)
			if input('\nEnter 1 to have first move else any other number: ')==1:
				flag=True
			else:
				flag=False
		elif chess.Move.from_uci(inp) in brd.legal_moves: #Dont get blank string here
			brd.push(chess.Move.from_uci(inp))
			print(brd)
			print('\n')
			print("Current FEN: "+brd.fen())
			print('\n')
			save_flag=True
			flag=False
		else:
			print("illegal move re-enter")
	else: #engine turn
		print("engine turn")
		eng.position(brd)
		bst,pon=eng.go(movetime=300)
		brd.push(bst)
		inp=bst.uci()
		print(brd)
		print('\n')
		print("Engine moved : ",inp)
		print("Current FEN: "+brd.fen())
		print('\n')
		save_flag=True
		flag=True

	if save_flag==True: #saving the move to the temporary pgn file
		pgn=open("/home/prabin/chess/Final/temp.pgn","w")
		node=game.end()
		node = node.add_variation(chess.Move.from_uci(inp))
		exporter = chess.pgn.FileExporter(pgn)
		game.accept(exporter)
		pgn.close()

#Game Termination
if os.path.exists("/home/prabin/chess/Final/temp.pgn"):
	os.remove("/home/prabin/chess/Final/temp.pgn")
print("END GAME")
