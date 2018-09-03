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


#include "Ui_Moc/GameTile.h"
extern bool active;

GameTile::GameTile(string hd,ros::NodeHandle _nh, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameTile), nh(_nh)
{
	ui->setupUi(this);
	header_data=hd;
	pub = nh.advertise<chess_bot::feature>("interactions", 1000);
	string temp="";
	for(int i=0;i<hd.size();i++)
	{
		if(hd[i]!=',')
			temp.push_back(hd[i]);
		else
		{
			headers.push_back(temp);
			temp="";
		}
	}
	headers.push_back(temp);
	
	ui->event->setText(QString(headers[0].c_str()));
	ui->round->setText(QString(headers[1].c_str()));
	ui->white->setText(QString(headers[2].c_str()));
	ui->black->setText(QString(headers[3].c_str()));	
}

void GameTile::on_play_clicked()
{
	if(!active)
	{
		chess_bot::feature fetmsg;
		fetmsg.head=header_data;
		fetmsg.flag=2;
		pub.publish(fetmsg);
		active=true;
	}
	else
		QMessageBox::information( this, tr("Information"), tr("One game is already running") );
}

void GameTile::on_del_clicked()
{
	chess_bot::feature fetmsg;
	fetmsg.head=header_data;
	fetmsg.flag=3;
	pub.publish(fetmsg);
}

GameTile::~GameTile()
{
    delete ui;
}
