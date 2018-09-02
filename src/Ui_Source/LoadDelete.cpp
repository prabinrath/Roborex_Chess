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


#include "Ui_Moc/LoadDelete.h"
extern string file_path;

LoadDelete::LoadDelete(ros::NodeHandle _nh, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoadDelete), nh(_nh)
{
	ui->setupUi(this);
	sub = nh.subscribe("ui_setup", 1, &LoadDelete::setScrollArea, this);
	loadTiles();
}

void LoadDelete::loadTiles()
{
	ifstream pgn;
	std::vector<GameTile*> gamelist;
	pgn.open(file_path+"/gamedata.pgn"); //open the pgn file in read mode
	if(pgn.is_open())
	{
		qDebug()<<"File opened\n";
	}
	else
	{
		qDebug()<<"Couldnt open the file\n";
	}
	string line,parm,send; //required string variables
	while(getline(pgn,line) && pgn.is_open()) //extract lines one by one
	{
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
				GameTile *temp=new GameTile(send,nh,this);
				gamelist.push_back(temp);
			}
			send="";
		}
	}
	pgn.close();
	
	if(!gamelist.empty())
	{
		QFrame *group = new QFrame();
		QVBoxLayout *vbox = new QVBoxLayout();
		vbox->setSpacing(0);
		group->setLayout(vbox);
		for(int i=0;i<gamelist.size();i++)
		{
			vbox->addWidget(gamelist[i]);
		}
		ui->scroll->setWidget(group);
    }
    else
    {
    	QMessageBox::information( this, tr("Information"), tr("No saved games found\nPlease close the Tab") );
    }
}

void LoadDelete::setScrollArea(const chess_bot::feature::ConstPtr& msg)
{
	if(msg->flag==2)
	{
		loadTiles();
	}
}

LoadDelete::~LoadDelete()
{
    delete ui;
}
