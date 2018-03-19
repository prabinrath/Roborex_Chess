#Test file for interfacing stockfish with user by Prabin

import chess
import chess.uci

eng=chess.uci.popen_engine("stockfish")
brd=chess.Board()
x=''

print("\nCHESS GAME CKECK 2\nDont enter wrong moves it will terminate the game\nEnter 'quit' to terminate manually\n")

choose=input('\nEnter 1 to have first move else any other number: ')
if choose==1:
	x=raw_input('Enter your move: ')
	if x=='quit':
			eng.quit()
	if chess.Move.from_uci(x) in brd.legal_moves:
		brd.push(chess.Move.from_uci(x))
		print(brd)
		print('\n')
		print("Current FEN: "+brd.fen())
		print('\n')
	else:
		print('illegal move game passed to Engine')

while(True):
	#engine turn
	print("engine turn")
	eng.position(brd)
	bst,pon=eng.go(movetime=3000)
	brd.push(bst)
	print(brd)
	print('\n')
	print("Engine moved : ",bst)
	print("Current FEN: "+brd.fen())
	print('\n')
	
	#user turn
	print("user turn")
	x=raw_input('Enter your move: ')
	if x=='quit':
			eng.quit()
			break
	if chess.Move.from_uci(x) in brd.legal_moves:
		brd.push(chess.Move.from_uci(x))
		print(brd)
		print('\n')
		print("Current FEN: "+brd.fen())
		print('\n')
	else:
		print("illegal move game terminated")
		eng.quit()
		break

print("END GAME")
