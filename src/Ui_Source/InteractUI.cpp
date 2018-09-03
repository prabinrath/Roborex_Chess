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


#include "Ui_Moc/InteractUI.h"
extern string file_path;

InteractUI::InteractUI(ros::NodeHandle _nh, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InteractUI), nh(_nh)
{
	ui->setupUi(this);
	//handle = new BoardUI(nh);
	//handle->show();
	setUI();
	aisend = nh.advertise<chess_bot::ui_data>("ui_recv", 1000);
	close_ui_flag = nh.advertise<std_msgs::Int32>("menu_data", 1000);
	interact = nh.advertise<chess_bot::feature>("interactions", 1000);
	airecv = nh.subscribe("ui_send", 10, &InteractUI::ui_callback, this);
	turn = nh.subscribe("turn_flag", 10, &InteractUI::setflag, this);
}

void InteractUI::on_send_clicked()
{
	QString indat=ui->sys_in->toPlainText();
	chess_bot::ui_data toui;
	toui.type=swh;
	if(swh==0 || swh==2)
	{
		toui.sys=indat.toStdString();
		aisend.publish(toui);
	}
}

void InteractUI::on_save_clicked()
{
	chess_bot::feature msg;
	msg.head="";
	msg.flag=1;
	interact.publish(msg);
	save_flag=true;
}

void InteractUI::on_undo_clicked()
{
	if(mv_cnt>2)
	{
		chess_bot::feature msg;
		msg.head="";
		msg.flag=2;
		interact.publish(msg);
		ui->move->removeRow(--mv_cnt);
		ui->move->removeRow(--mv_cnt);
		save_flag=false;
	}
}

void InteractUI::on_rst_clicked()
{
	chess_bot::feature msg;
	msg.head="";
	QMessageBox::StandardButton reply=QMessageBox::question(this,tr("Confirm Exit"),tr("Would you like to move first?"),QMessageBox::Yes|QMessageBox::No);
	if(reply==QMessageBox::Yes)
	{
		msg.head="y";
	}
	msg.flag=3;
	interact.publish(msg);
	while(mv_cnt>0)
		ui->move->removeRow(--mv_cnt);		
}

void InteractUI::setflag(const std_msgs::Bool::ConstPtr& msg)
{
	master=msg->data;
}

void InteractUI::insertRecord(string data)
{
	ifstream rfile; 
   	ofstream wfile;
   	wfile.open(file_path+"/temp.txt");
   	rfile.open(file_path+"/textdata.txt"); 
   	if(rfile.is_open() && wfile.is_open())
	{
		qDebug()<<"Files opened\n";
	}
	else
	{
		qDebug()<<"Couldn't open the files\n";
	}
 
    string line="";
	while (getline(rfile, line) && rfile.is_open() && wfile.is_open())
	{
	    wfile<<line<<endl;
	    if(line=="#record")
	    {
		getline(rfile, line);
		if(line=="NO RECORDS FOUND")
		    wfile<<data<<endl;
		else
		{
			wfile<<line<<endl;
			while(getline(rfile, line))
			{
				if(line != "#")
				   wfile<<line<<endl;
			}
			wfile<<data<<endl;
			wfile<<"#"<<endl;
		}
	    }
	}
   	rfile.close();
   	wfile.close();
   	if(line != "")
	{
		remove((file_path+"/textdata.txt").c_str());
		rename((file_path+"/temp.txt").c_str() , (file_path+"/textdata.txt").c_str());
	}
}

void InteractUI::ui_callback(const chess_bot::ui_data::ConstPtr& msg)
{
	swh=msg->type;
	if(swh!=4)
	{
		//ui->sys_out->setText(QString(msg->sys.c_str()));
		QString ui_msg=QString(msg->sys.c_str());
		if(ui_msg.contains(QString("draw")))
		{
			insertRecord((QString(user_name.c_str())+QString(" draw ")+QString::number(mv_cnt-1)).toStdString());
		}
		if(ui_msg.contains(QString("congratulations")))
		{
			insertRecord((QString(user_name.c_str())+QString(" congratulations ")+QString::number(mv_cnt-1)).toStdString());
		}
		QMessageBox::information( this, tr("System Says..."), ui_msg);
	}
	else
	{
		if(master==false)
		{
			ui->move->setItem(mv_cnt, 0, new QTableWidgetItem(QString(user_name.c_str())));
			ui->move->setItem(mv_cnt, 1, new QTableWidgetItem(QString(msg->mo.c_str())));
		}
		else
		{
			ui->move->setItem(mv_cnt, 0, new QTableWidgetItem("stockfish"));
			ui->move->setItem(mv_cnt, 1, new QTableWidgetItem(QString(msg->mo.c_str())));
		}
		mv_cnt++;
		save_flag=false;
	}
}

void InteractUI::setUI()
{
	swh=4;mv_cnt=0;
	master=false;save_flag=true;
	ui->move->setRowCount(100);
	ui->move->setStyleSheet("QTableView {selection-background-color: rgb(255,228,181);}");
	
	ifstream lst;
	lst.open(file_path+"/uci_list.txt"); //open the pgn file in read mode
	if(lst.is_open())
	{
		qDebug()<<"File opened\n";
	}
	else
	{
		qDebug()<<"Couldn't open the file\n";
	}
	string line,mov="";
	while(getline(lst,line) && lst.is_open()) //extract lines one by one
	{
		for(int i=2;i<line.size();i++)
		{
			mov.push_back(line[i]);
		}
		if(line[0]=='0')
		{
			ui->move->setItem(mv_cnt, 0, new QTableWidgetItem(QString(user_name.c_str())));
			ui->move->setItem(mv_cnt, 1, new QTableWidgetItem(QString(mov.c_str())));
			mv_cnt++;
		}
		else if(line[0]=='1')
		{
			ui->move->setItem(mv_cnt, 0, new QTableWidgetItem("Stockfish"));
			ui->move->setItem(mv_cnt, 1, new QTableWidgetItem(QString(mov.c_str())));
			mv_cnt++;
		}
		else
		{
			user_name=line;
		}
		mov="";
	}
	lst.close();

	if(remove((file_path+"/uci_list.txt").c_str())!=0)
		qDebug()<<"Couldn't find initializer list\n";
	else
		qDebug()<<"Deleted initializer list successfully\n";
}

void InteractUI::closeEvent(QCloseEvent *evt)
{
	QMessageBox::StandardButton replyA=QMessageBox::question(this,tr("Confirm Exit"),tr("Thanks for playing\nDo you want to Quit this game session?"),QMessageBox::Yes|QMessageBox::No);
	if(replyA==QMessageBox::Yes)
	{
		if(save_flag==false)
		{
			QMessageBox::StandardButton replyB=QMessageBox::question(this,tr("Save"),tr("Do you want to save the current game?"),QMessageBox::Yes|QMessageBox::No);
			if(replyB==QMessageBox::Yes)
			{
				chess_bot::feature msg;
				msg.head="";
				msg.flag=1;
				interact.publish(msg);
			}
		}
		std_msgs::Int32 close_flag;
		close_flag.data=0;
		close_ui_flag.publish(close_flag);
		evt->accept();
	}
	else
		evt->ignore();
}


InteractUI::~InteractUI()
{
    delete ui;
}

//TODO:Merge Board UI with Interaction UI
