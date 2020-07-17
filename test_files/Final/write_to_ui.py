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

import os
import chess.pgn
#write the pgn data in uci format to a file such that a cpp code can load the moves to the UI afer game retrival from save or crash.
game=chess.pgn.Game()
game.headers["Event"]="Hello"
game.headers["White"]="prabin"
game.headers["Black"]="Stockfish"
game.headers["Round"]="1"
new_text = open("game_write.txt","w")
if(game.headers["Black"]=="Stockfish"):
	tagA="0 ";tagB="1 ";
	new_text.write( game.headers["White"] )
else:
	tagA="1 ";tagB="0 ";
	new_text.write( game.headers["Black"] )
length=len(game.root().variations);
if length>0:
	node = game.root().variations[0];
node_ = game.end();
if length>0:
	while(node.move.uci()!=node_.move.uci()):
		try:
			new_text.write( tagA+node.move.uci()+"\n" )
			node = node.variations[0]
			new_text.write( tagB+node.move.uci()+"\n" )
			node = node.variations[0]
		except:
			pass
new_text.close()
