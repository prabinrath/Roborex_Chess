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
## AUTHORS: Pabitra Dash, Swostik Acharya
##
################################################################################

def func(mat_1,mat_2):
    a=mat_1[:];s=mat_2[:]
    i,j=0,0
    for j in range(4):
        a[j],a[7-j]=a[7-j],a[j]
        s[j],s[7-j]=s[7-j],s[j]
    d=[]
    f1,f2,t1,t2=99,99,0,0
    for i in range(8):
        for j in range(8):
            if a[i][j]!=s[i][j]:
                d.append(i)
                d.append(j)
    f1,f2,t1,t2=d[0],d[1],d[2],d[3]
    if a[f1][f2]==1:
        pass
    else:
        f1,t1=t1,f1 # swaps
        f2,t2=t2,f2 #swap
    f1+=1;t1+=1;f2+=1;t2+=1
    po=[1,2,3,4,5,6,7,8];op=['a','b','c','d','e','f','g','h']
    for i in range(8):
        if f2==po[i]:
            f2=op[i]
        if t2==po[i]:
            t2=op[i]
            pass
    f1=str(f1);t1=str(t1)
    print("The move performed is:-  ")
    print(f2+f1+t2+t1)

#Give input of  the binary matrices
first=[[1,1,1,1,1,1,1,1],[1,1,1,1,1,1,1,1],[0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0],[0,0,0,0,1,0,0,0],
[0,0,0,0,0,0,0,0],[1,1,1,1,0,1,1,1],[1,1,1,1,1,1,1,1]]
second=[[1,1,1,1,1,1,0,1],[1,1,1,1,1,1,1,1],[0,0,0,0,0,1,0,0],[0,0,0,0,0,0,0,0],[0,0,0,0,1,0,0,0],
[0,0,0,0,0,0,0,0],[1,1,1,1,0,1,1,1],[1,1,1,1,1,1,1,1]]
#call the function
func(first,second)
