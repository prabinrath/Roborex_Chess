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


#include "Ui_Moc/About.h"
using namespace std;

string FILE_PATH = ros::package::getPath("chess_bot") + "/files";

About::About(string tag,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::About)
{
	ui->setupUi(this);
	setOutput(tag);
}

void About::setOutput(string query_tag)
{
	string temp,file_tag,output="";
	ifstream newfile;
	newfile.open(FILE_PATH+"/textdata.txt",ios::in);
	if(!newfile.is_open())
		{qDebug()<<"File not found\n";}
	while(getline(newfile,temp) && newfile.is_open())
	{
		if(temp[0]=='#' && temp.length()>1)
		{
			for(int i=1;i<temp.length();i++)
				{file_tag.push_back(temp[i]);}
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
	if(output=="")
		{qDebug()<<"No such tag found";}
	else
		{ui->text->setText(Qstring(output.c_str()));}
}

About::~About()
{
    delete ui;
}
