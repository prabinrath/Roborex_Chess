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


#include "Ui_Moc/NewGame.h"
extern string file_path;
extern bool active;

NewGame::NewGame(ros::NodeHandle _nh, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewGame), nh(_nh)
{
	ui->setupUi(this);
	pub = nh.advertise<chess_bot::feature>("interactions", 1000);
}

bool NewGame::checkPresence(string head)
{
	bool is_present=false;
	ifstream pgn;
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
				if(send==head)
					is_present=true;
			}
			send="";
		}
	}
	pgn.close();
	return is_present;
}

void NewGame::on_confirm_clicked()
{
   if(ui->event->toPlainText()!="" && ui->name->toPlainText()!="" && ui->round->toPlainText()!="" && !active)
   {
	   QString header;
	   header+=ui->event->toPlainText()+","+ui->round->toPlainText()+",";
	   if(ui->first->isChecked())
	   		header+=ui->name->toPlainText()+",Stockfish";
	   else
	   		header+="Stockfish,"+ui->name->toPlainText();
	   //qDebug()<<header;
	   if(checkPresence(header.toStdString())==true)
	   	{
	   		QMessageBox::StandardButton reply=QMessageBox::question(this,tr("Concurrency Found"), tr("Incomplete game with similar parameters is already present in the Saved Game List, Would you like to delete that game and start a new one?") ,QMessageBox::Yes|QMessageBox::No);
	   		if(reply==QMessageBox::Yes)
			{
				fetmsg.head=header.toStdString();
				fetmsg.flag=3;
				pub.publish(fetmsg);
				fetmsg.flag=1;
				pub.publish(fetmsg);
				this->hide();
			}
	   	}
	   	else
	   	{
	   		fetmsg.head=header.toStdString();
	   		fetmsg.flag=1;
			pub.publish(fetmsg);
			this->hide();
	   	}
	   	active=true;
	}
	else
	{
		if(active==true)
		{
			QMessageBox::information( this, tr("Information"), tr("One game is already running") );
		}
		else
			QMessageBox::information( this, tr("Information"), tr("None of the fields can be left blank") );
	}		
}

NewGame::~NewGame()
{
    delete ui;
}
