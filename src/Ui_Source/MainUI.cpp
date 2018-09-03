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


#include "Ui_Moc/MainUI.h"
extern bool active;

MainUI::MainUI(ros::NodeHandle _nh, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainUI), nh(_nh)
{
	ui->setupUi(this);
	feature_command = nh.advertise<chess_bot::feature>("interactions", 1000);
	set = nh.subscribe("ui_setup", 1, &MainUI::setUI, this);
	menu_command = nh.subscribe("menu_data", 1, &MainUI::tabControl, this);
	ui->TabHandle->removeTab(1);ui->TabHandle->removeTab(0);
    ui->TabHandle->addTab(new Menu(nh,this),"Menu");menu_flg=0;
    newgame_flg=-1;loadgame_flg=-1;record_flg=-1;inst_flg=-1;credit_flg=-1;
}

void MainUI::tabControl(const std_msgs::Int32::ConstPtr& msg)
{
	if(msg->data==0)
	{
		interactUI=NULL;
		if(newgame_flg!=-1)
			{ui->TabHandle->removeTab(newgame_flg);newgame_flg=-1;}
		if(loadgame_flg!=-1)
			{ui->TabHandle->removeTab(loadgame_flg);loadgame_flg=-1;}
		boardUI->close();
		active=false;
	}
	else if(msg->data==1)
	{
		if(interactUI==NULL)
		{
			if(newgame_flg==-1 && loadgame_flg==-1)
				{ui->TabHandle->addTab(new NewGame(nh,this),"New Game");newgame_flg=ui->TabHandle->count()-1;}
			else
				QMessageBox::information( this, tr("Information"), tr("Either New game tab or Saved Game List tab is already open") );
		}
		else
		{
			QMessageBox::information( this, tr("Information"), tr("One game is already running") );
		}
		if(newgame_flg!=-1)
			ui->TabHandle->setCurrentIndex(newgame_flg);
		else
			ui->TabHandle->setCurrentIndex(loadgame_flg);
	}
	else if(msg->data==2)
	{
		if(interactUI==NULL)
		{
			if(newgame_flg==-1 && loadgame_flg==-1)
				{ui->TabHandle->addTab(new LoadDelete(nh,this),"Saved Game List");loadgame_flg=ui->TabHandle->count()-1;}
			else
				QMessageBox::information( this, tr("Information"), tr("Either New game tab or Saved Game List tab is already open") );
		}
		else
		{
			QMessageBox::information( this, tr("Information"), tr("One game is already running") );
		}
		if(loadgame_flg!=-1)
			ui->TabHandle->setCurrentIndex(loadgame_flg);
		else
			ui->TabHandle->setCurrentIndex(newgame_flg);
	}
	else if(msg->data==3)
	{
		if(record_flg==-1)
			{ui->TabHandle->addTab(new About("record",this),"Game Record");record_flg=ui->TabHandle->count()-1;}
		ui->TabHandle->setCurrentIndex(record_flg);
	}
	else if(msg->data==4)
	{
		if(inst_flg==-1)
			{ui->TabHandle->addTab(new About("instruction",this),"Instructions");inst_flg=ui->TabHandle->count()-1;}
		ui->TabHandle->setCurrentIndex(inst_flg);
	}
	else if(msg->data==5)
	{
		if(credit_flg==-1)
			{ui->TabHandle->addTab(new About("credit",this),"Credits");credit_flg=ui->TabHandle->count()-1;}
		ui->TabHandle->setCurrentIndex(credit_flg);
	}
}

void MainUI::setUI(const chess_bot::feature::ConstPtr& msg)
{
	if(msg->flag==1)
	{
		boardUI=new QProcess();
    	boardUI->start(QString("rosrun chess_ui_fen chess_ui_fen"));
    	interactUI=new InteractUI(nh,this);
    	interactUI->show();
	}
}

void MainUI::on_TabHandle_tabCloseRequested(int index)
{
   if(index!=0)
   {
   		ui->TabHandle->removeTab(index);
   		if(index==newgame_flg)
   			newgame_flg=-1;
   		else if(index==loadgame_flg)
   			loadgame_flg=-1;
   		else if(index==record_flg)
   			record_flg=-1;
   		else if(index==inst_flg)
   			inst_flg=-1;
   		else if(index==credit_flg)
   			credit_flg=-1;
   }
}

void MainUI::closeEvent(QCloseEvent *evt)
{
		QMessageBox::StandardButton replyA=QMessageBox::question(this,tr("Confirm Exit"),tr("Thanks for playing\nDo you want to Quit?"),QMessageBox::Yes|QMessageBox::No);
		if(replyA==QMessageBox::Yes)
		{
			fetmsg.head="";fetmsg.flag=4;
			if(interactUI!=NULL)
			{
				QMessageBox::StandardButton replyB=QMessageBox::question(this,tr("Save"),tr("Do you want to save the current game?"),QMessageBox::Yes|QMessageBox::No);
				if(replyB==QMessageBox::Yes)
					fetmsg.flag=5;
			}
			feature_command.publish(fetmsg);
			evt->accept();
		}
		else
			evt->ignore();
}

MainUI::~MainUI()
{
    delete ui;
}
