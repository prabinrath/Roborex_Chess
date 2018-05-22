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
// AUTHORS: Subham Sahoo, Neelam Mahapatro
//
////////////////////////////////////////////////////////////////////////////////


#include"iostream"
#include"fstream"
#include"string"
using namespace std;

string setOutput(string query_tag)
{
	string temp,file_tag,output="";
	ifstream newfile;
	newfile.open("/home/prabin/catkin_ws/src/chess_bot/test_files/Final/textdata.txt",ios::in);
	if(!newfile.is_open())
		cout<<"File not found\n";
	while(getline(newfile,temp) && newfile.is_open())
	{
		if(temp[0]=='#' && temp.length()>1)
		{
			for(int i=1;i<temp.length();i++)
				{file_tag.push_back(temp[i]);}
				//cout<<file_tag<<endl;
			if(file_tag==query_tag)
			{
				while(getline(newfile,temp))
				{
					if(temp=="#")
						{break;}
					else
					{output+=temp;output+="\n";}
				}
			}
			file_tag="";
		}
	}
	return output;
}

int main()
{
	string query_tag;
	cin>>query_tag;
	if(setOutput(query_tag)=="")
		cout<<"Data not Found\n";
	else
		cout<<setOutput(query_tag);
}

