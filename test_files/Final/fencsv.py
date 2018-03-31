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
## AUTHORS: Subham Sahoo, Swostik Acharya, Pabitra Dash
##
################################################################################

import six
import csv

pieces_str = "PNBRQK"
pieces_str += pieces_str.lower()
pieces = set(pieces_str)
valid_spaces = set(range(1,9))

def tofen(csvstr):
    '''It loads a csv str and convert to fen string'''
    sio = six.StringIO(csvstr)
    sio.seek(0)
    reader = csv.reader(sio, delimiter='|', quoting=csv.QUOTE_MINIMAL)
    board = [r for r in reader]
    descstr = ' '.join(board[0])
    board = board[1:]
    boardstr = []
    rowstr = []
    for row in board:
        spaces = 0
        for c in row:
            if c == ' ':
                spaces += 1
            else:
                if spaces:
                    rowstr.append(str(spaces))
                    spaces = 0
                rowstr.append(c)
        if spaces:
            rowstr.append(str(spaces))
        boardstr.append(''.join(rowstr))
        rowstr = []

    return '/'.join(boardstr) + ' ' + descstr


def tocsv(fenstr):
    '''Load a fen str and convert to csv'''
    fen = fenstr.split()
    boardstr, desc = fen[0], fen[1:]
    # convert the board to rows of either a piece or a space
    board = [desc]  # description is the header
    cur_row = []
    for i, c in enumerate(boardstr):
        if c in pieces:
            cur_row.append(c)
        elif c == '/':  # new row
            board.append(cur_row)
            cur_row = []
        elif int(c) in valid_spaces:
            cur_row.extend(' ' * int(c))
        else:
            raise ValueError("invalid fenstr at index: {} char: {}"
                             .format(i, c))
    board.append(cur_row)
    sio = six.StringIO()
    writer = csv.writer(sio, delimiter='|', quoting=csv.QUOTE_MINIMAL,
                        lineterminator='\n')
    writer.writerows(board)
    return sio.getvalue()


if __name__ == '__main__':
    fen = raw_input("enter the fenstr ")
    csvtxt = tocsv(fen)
    refen = tofen(csvtxt)
    print(tocsv(fen))
    print("compare:")
    print(fen)
    print(refen)
    assert refen == fen # it checks the assertion if the code assumptions are right or wrong
#note : see there is something called delimeter it makes the difference as u want
# Its in classic format
# You can call it in modern 2.7 way also
