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

#This code talks with the Stockfish Chess Engine. Entries are to be made in algebraic
#chess notation (eg. e2e4). Stockfish is set to think for a maximum of 1 sec.

import sys

chess = r'/Applications/stockfish-4-mac/Mac/stockfish-4-64'.split()['linux' in sys.platform]

import subprocess as S
getprompt = 'isready'
done= 'readyok'

proc= S.Popen(chess, stdin=S.PIPE, stdout=S.PIPE, bufsize=1, universal_newlines=True)

print(proc.stdout.readline().strip())
proc.stdin.write('uci\n')

while True :
        text = proc.stdout.readline().strip()
        print(text)
        if text == "uciok":
            break
        
print('Choose skill level (0-20):')
skillLevel=input()
proc.stdin.write('setoption name Skill Level value '+skillLevel+'\n')
proc.stdin.write('ucinewgame\n')

moveList='position startpos moves '
checkmate=False
while checkmate==False:
    print('Enter move:')
    move=input()
    moveList=moveList+move+' '
    proc.stdin.write(moveList+'\n')
    proc.stdin.write('go movetime 1000\n')
    print('Computer moves:')
    while True :
        text = proc.stdout.readline().strip()
        if text[0:8] == 'bestmove':
            cpuMove=text[9:13]
            print(cpuMove)
            moveList=moveList+cpuMove+' '
            break
