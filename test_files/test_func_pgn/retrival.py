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
## AUTHORS: Pabitra Dash, Swostik Acharya, Prabin Rath, Neelam Mahapatro
##
################################################################################


import chess
import chess.pgn

def fun_nth_retrival(event,white,black,round1):
    new_pgn=open("/home/pabitra/Desktop/Adams.pgn")
    i=0
    for i,headers in chess.pgn.scan_headers(new_pgn):
        if(headers["Event"]==event) and (headers["White"]==white) and (headers["Black"]==black) and (headers["Round"]==round1):
            game=chess.pgn.read_game(new_pgn)
            game.headers["Event"]=headers["Event"]
            game.headers["White"]=headers["White"]
            game.headers["Black"]=headers["Black"]
            game.headers["Round"]=headers["Round"]
            print(game)
            brd=game.board()
            for move in game.main_line():
                brd.push(move)
    return brd

event=raw_input("Enter the name of event: ")
white=raw_input("Player in White side: ")
black=raw_input("Player in black side: ")
round1=raw_input("Enter the round number: ")
brd=fun_nth_retrival(event,white,black,round1)
print(brd)
