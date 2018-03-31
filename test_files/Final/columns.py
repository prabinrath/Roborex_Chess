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
## AUTHORS: Prabin Rath, Subham Sahoo, Pabitra Das
##
################################################################################

s="00010000,01000000,00010000,10000100,01001001,01000010,01001000,10100010"
q=''
s=s.split(',')
i,j=0,0
while i<8:
	if (i%2==0):
		s[i]=list(s[i])
		s[i].reverse()
		''.join(s[i])
	else:
		s[i]=list(s[i])
		for j in range(0,8,2):
			s[i][j],s[i][j+1]=s[i][j+1],s[i][j]
			''.join(s[i])
	i=i+1
j=0
for j in range(1,9,2):
	s[j].reverse()
i=0
while i<4:
	s[i],s[7-i]=s[7-i],s[i]
	i=i+1
i,j=0,0
while j<8:
	w=s[0][j]+s[1][j]+s[2][j]+s[3][j]+s[4][j]+s[5][j]+s[6][j]+s[7][j]
	q=q+w
	if (j<=6):
		q=q+','
	j=j+1
print(q)
	
