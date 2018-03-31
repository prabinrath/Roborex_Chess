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
import chess.pgn

game=chess.pgn.Game()
brd=chess.Board()

node=game.end()
brd.push(chess.Move.from_uci('e2e4'))
node=node.add_variation(chess.Move.from_uci('e2e4'))

node=game.end()
brd.push(chess.Move.from_uci('e7e5'))
node=node.add_variation(chess.Move.from_uci('e7e5'))

node=game.end()
brd.push(chess.Move.from_uci('c2c4'))
node=node.add_variation(chess.Move.from_uci('c2c4'))

node=game.end()
brd.push(chess.Move.from_uci('c7c5'))
node=node.add_variation(chess.Move.from_uci('c7c5'))

print(brd)
print(game)

print(node.move)

node.parent.remove_variation(brd.pop())
del node
node=game.end()
node.parent.remove_variation(brd.pop())
del node
node=game.end()

node=game.end()
brd.push(chess.Move.from_uci('h2h4'))
node=node.add_variation(chess.Move.from_uci('h2h4'))

print(brd)
print(game)
