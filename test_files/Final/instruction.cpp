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

string fun(int a)
{
	int count=-1,check=0;
	string value="",temp;
	ifstream newfile;
	newfile.open("final_text.txt",ios::in);
	while(getline(newfile,temp))
	{
		if(a==count && temp[0]!='#')
		{
			check=1;
			if(value=="")
				value+=temp;
			else
				value+="\n"+temp;
		}
		else if(temp[0]=='#')
		{	
			if(check==1)
			{
				newfile.close();
				return value;
			}
			count++;
		}
	}


	/**if(a==0)
	{
		newfile.read((char*)&inst,sizeof(inst));
		while(!newfile.eof())
	}
	else if(a==1)
	{
		newfile.read((char*)&inst,sizeof(inst));
	}**/
}

int main()
{
	int a;
	cin>>a;
	cout<<fun(a);
}

