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
## AUTHORS: Pabitra Dash
##
################################################################################

import chess
import chess.uci
brd=chess.Board()

def checking(string_):
    len_value=len(string_)
    if len_value==4:
        fuck=checking_(string_)
    if len_value==5:
        fuck='5'
    return fuck


def checking_(string_):
    flag=99
    string_=chess.Move.from_uci(string_)
    if(brd.is_capture(string_)):
        flag='1'
    if(brd.is_en_passant(string_)):
        flag='2'
    if(brd.is_castling(string_)):
        flag='3'
    if(flag==99):
        flag='0'
    return flag

###################################
i=0
while True:
    str_=raw_input("Enter a string: ")
    i=i+1
    a=checking(str_)
    print(a)
    brd.push(chess.Move.from_uci(str_))
    print(brd)
    '''
    if(i%2==0):
        a=checking(str_)
        print(a)
    '''
