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
## AUTHORS: Pabitra Dash, Neelam Mahapatro, Swostik Acharya, Prabin Rath
##
################################################################################


import os
import os.path
import chess
import chess.pgn

def nth_deletion(event,white,black,round_):
    new=open("/home/pabitra/Desktop/Adams.pgn")
    i=0
    game_data=open("/home/pabitra/Desktop/tempo.pgn","w")
    for i,headers in chess.pgn.scan_headers(new):
        if(headers["Event"]==event) and (headers["White"]==white) and (headers["Black"]==black) and (headers["Round"]==round_):
            continue
        else:
            game=chess.pgn.read_game(new)
            game.headers["Event"]=headers["Event"]
            game.headers["White"]=headers["White"]
            game.headers["Black"]=headers["Black"]
            game.headers["Round"]=headers["Round"]
            exporter=chess.pgn.FileExporter(game_data)
            game.accept(exporter)
    game_data.close()
    os.remove("/home/pabitra/Desktop/Adams.pgn")
    os.rename("/home/pabitra/Desktop/tempo.pgn","/home/pabitra/Desktop/Adams.pgn")

if os.path.exists("/home/pabitra/Desktop/temp.pgn"):
	print("found")
	new_pgn=open("/home/pabitra/Desktop/temp.pgn")
        game=chess.pgn.read_game(new_pgn)   #  eithi asiba katha #check for content of temp.pgn
        brd=game.board()
        for move in game.main_line():
		brd.push(move) 
else:
        print("not found")
        brd=chess.Board()
	game=chess.pgn.Game()

flag=True
while(True):
	if(flag==True):
		x=raw_input("Enter white move: ")
		flag=False
	else:
		x=raw_input("Enter black move: ")
		flag=True
	if x=='save':
		if os.path.exists("/home/pabitra/Desktop/Adams.pgn"):	
			pgn_=open("/home/pabitra/Desktop/Adams.pgn")
			for i,headers in chess.pgn.scan_headers(pgn_):
				if(headers["Event"]==game.headers["Event"]) and (headers["White"]==game.headers["White"]) and (headers["Black"]==game.headers["Black"]) and (headers["Round"]==game.headers["Round"]):
					pgn_.close()
					nth_deletion(game.headers["Event"],game.headers["White"],game.headers["Black"],game.headers["Round"])
					break #check this condition
			pgn_.close()
		pgn_=open("/home/pabitra/Desktop/Adams.pgn","a") #add newline before saving
		exporter = chess.pgn.FileExporter(pgn_)
		game.accept(exporter)
		pgn_.close()
	elif x=='quit':
		break		
	else:
		pgn=open("/home/pabitra/Desktop/temp.pgn","w")
		node=game.end()
		node = node.add_variation(chess.Move.from_uci(x))
		exporter = chess.pgn.FileExporter(pgn)
		game.accept(exporter)
		pgn.close()
os.remove("/home/pabitra/Desktop/temp.pgn")
