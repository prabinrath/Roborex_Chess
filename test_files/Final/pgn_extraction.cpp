////////////////////////////////////////////////////////////////////////////////
//
// MIT License
//
// Copyright (c) 2018 Team Roborex, NIT Rourkela
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// AUTHORS: Prabin Rath
//
////////////////////////////////////////////////////////////////////////////////

//pgn parameter extration from .pgn file. Required to be integrated in the UI code.
#include<iostream>
#include<fstream>
#include<string>
//#include<sstream>

using namespace std;

main()
{
	ifstream pgn;
	pgn.open("/home/prabin/chess/Final/gamedata.pgn"); //open the pgn file in read mode
	if(pgn.is_open())
	{
		cout<<"File opened\n";
	}
	else
	{
		cout<<"Couldnt open the file\n";
	}
	string line,parm,send; //required string variables
	while(getline(pgn,line) && pgn.is_open()) //extract lines one by one
	{
		//istringstream iss(line); //to get string tokens
		//logic for parameter extration from the string
		if(line[0]=='[')
		{
			int i=1;
			while(line[i]!=' ')
			{
				parm.push_back(line[i]);i++;
			}
			i+=2;
			if(parm=="Event" || parm=="White" || parm=="Black" || parm=="Round")
			{
				while(line[i]!='"')
				{
					send.push_back(line[i]);i++;
				}
				if(parm!="Black")
				{
					send.push_back(',');
			 	}
			}
			parm="";
		}
		else if(line[0]='\n')
		{
			if(send!="")
			{
				cout<<send.c_str()<<endl;
			}
			send="";
		}
	}
	pgn.close();
	return 0;
}
