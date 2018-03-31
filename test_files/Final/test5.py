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
