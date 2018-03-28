#include "BoardUI.h"
#include "ui_BoardUI.h"

BoardUI::BoardUI(ros::NodeHandle _nh, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BoardUI), nh(_nh)
{
	ui->setupUi(this);
	setboard();
	sub = nh.subscribe("fendata", 10, &BoardUI::callback, this);
	turn = nh.subscribe("turn_flag", 10, &BoardUI::setflag, this);
}

void BoardUI::callback(const std_msgs::String::ConstPtr& msg)
{
	setfen(QString(msg->data.c_str()));
}

void BoardUI::setfen(QString fen)
{
	int i,j,k,q;
	ui->fen->setText(fen);

	for(i=0;i<64;i++)
	{
		leb[i]->setPixmap(blnk);
	}
	i=56;q=0;
	while(fen[q]!=' ')
	{
		if(fen.at(q).isDigit())
		{
			k=fen.at(q).digitValue();
			for(j=0;j<k;j++)i++;
		}
		else if(fen[q]=='r'){leb[i]->setPixmap(rok_b);i++;}
		else if(fen[q]=='n'){leb[i]->setPixmap(nit_b);i++;}
		else if(fen[q]=='b'){leb[i]->setPixmap(bis_b);i++;}
		else if(fen[q]=='k'){leb[i]->setPixmap(kin_b);i++;}
		else if(fen[q]=='q'){leb[i]->setPixmap(que_b);i++;}
		else if(fen[q]=='p'){leb[i]->setPixmap(pwn_b);i++;}
		else if(fen[q]=='R'){leb[i]->setPixmap(rok_w);i++;}
		else if(fen[q]=='N'){leb[i]->setPixmap(nit_w);i++;}
		else if(fen[q]=='B'){leb[i]->setPixmap(bis_w);i++;}
		else if(fen[q]=='K'){leb[i]->setPixmap(kin_w);i++;}
		else if(fen[q]=='Q'){leb[i]->setPixmap(que_w);i++;}
		else if(fen[q]=='P'){leb[i]->setPixmap(pwn_w);i++;}
		else if(fen[q]=='/'){i-=16;}
	q++;
	}
}

void BoardUI::setflag(const std_msgs::Bool::ConstPtr& msg)
{
	if(msg->data==false)
	{ui->chnc_2->setPixmap(blnk);ui->chnc_1->setPixmap(chnc);}
	else
	{ui->chnc_1->setPixmap(blnk);ui->chnc_2->setPixmap(chnc);}
}

void BoardUI::setboard()
{
	int i,j;
	//int w=ui->lab_1->width(),h=ui->lab_1->height();

	leb[0]=ui->lab_1;leb[1]=ui->lab_2;leb[2]=ui->lab_3;leb[3]=ui->lab_4;
	leb[4]=ui->lab_5;leb[5]=ui->lab_6;leb[6]=ui->lab_7;leb[7]=ui->lab_8;
	leb[8]=ui->lab_9;leb[9]=ui->lab_10;leb[10]=ui->lab_11;leb[11]=ui->lab_12;
	leb[12]=ui->lab_13;leb[13]=ui->lab_14;leb[14]=ui->lab_15;leb[15]=ui->lab_16;
	leb[16]=ui->lab_17;leb[17]=ui->lab_18;leb[18]=ui->lab_19;leb[19]=ui->lab_20;
	leb[20]=ui->lab_21;leb[21]=ui->lab_22;leb[22]=ui->lab_23;leb[23]=ui->lab_24;
	leb[24]=ui->lab_25;leb[25]=ui->lab_26;leb[26]=ui->lab_27;leb[27]=ui->lab_28;
	leb[28]=ui->lab_29;leb[29]=ui->lab_30;leb[30]=ui->lab_31;leb[31]=ui->lab_32;
	leb[32]=ui->lab_33;leb[33]=ui->lab_34;leb[34]=ui->lab_35;leb[35]=ui->lab_36;
	leb[36]=ui->lab_37;leb[37]=ui->lab_38;leb[38]=ui->lab_39;leb[39]=ui->lab_40;
	leb[40]=ui->lab_41;leb[41]=ui->lab_42;leb[42]=ui->lab_43;leb[43]=ui->lab_44;
	leb[44]=ui->lab_45;leb[45]=ui->lab_46;leb[46]=ui->lab_47;leb[47]=ui->lab_48;
	leb[48]=ui->lab_49;leb[49]=ui->lab_50;leb[50]=ui->lab_51;leb[51]=ui->lab_52;
	leb[52]=ui->lab_53;leb[53]=ui->lab_54;leb[54]=ui->lab_55;leb[55]=ui->lab_56;
	leb[56]=ui->lab_57;leb[57]=ui->lab_58;leb[58]=ui->lab_59;leb[59]=ui->lab_60;
	leb[60]=ui->lab_61;leb[61]=ui->lab_62;leb[62]=ui->lab_63;leb[63]=ui->lab_64;


	kin_w.load("/home/prabin/catkin_ws/src/chess_bot/utils/king_white.svg");
	que_w.load("/home/prabin/catkin_ws/src/chess_bot/utils/queen_white.svg");
	nit_w.load("/home/prabin/catkin_ws/src/chess_bot/utils/knight_white.svg");
	bis_w.load("/home/prabin/catkin_ws/src/chess_bot/utils/bishop_white.svg");
	rok_w.load("/home/prabin/catkin_ws/src/chess_bot/utils/rook_white.svg");
	pwn_w.load("/home/prabin/catkin_ws/src/chess_bot/utils/pawn_white.svg");
	kin_b.load("/home/prabin/catkin_ws/src/chess_bot/utils/king_black.svg");
	que_b.load("/home/prabin/catkin_ws/src/chess_bot/utils/queen_black.svg");
	nit_b.load("/home/prabin/catkin_ws/src/chess_bot/utils/knight_black.svg");
	bis_b.load("/home/prabin/catkin_ws/src/chess_bot/utils/bishop_black.svg");
	rok_b.load("/home/prabin/catkin_ws/src/chess_bot/utils/rook_black.svg");
	pwn_b.load("/home/prabin/catkin_ws/src/chess_bot/utils/pawn_black.svg");
	chnc.load("/home/prabin/catkin_ws/src/chess_bot/utils/exp.png");
	prof.load("/home/prabin/catkin_ws/src/chess_bot/utils/profile.png");
	stk.load("/home/prabin/catkin_ws/src/chess_bot/utils/stk.jpeg");

	for(i=0;i<64;i+=16)
	{
		for(j=0;j<8;j++)
		{
			if(j%2==0)
			leb[i+j]->setStyleSheet("QLabel {background-color: rgb(120, 120, 90);}");
			else
			leb[i+j]->setStyleSheet("QLabel {background-color: rgb(211, 211, 158);}");
		}
	}
	for(i=8;i<64;i+=16)
	{
		for(j=0;j<8;j++)
		{
			if(j%2!=0)
			leb[i+j]->setStyleSheet("QLabel {background-color: rgb(120, 120, 90);}");
			else
			leb[i+j]->setStyleSheet("QLabel {background-color: rgb(211, 211, 158);}");
		}
	}

	leb[0]->setPixmap(rok_w);leb[7]->setPixmap(rok_w);
	leb[1]->setPixmap(nit_w);leb[6]->setPixmap(nit_w);
	leb[2]->setPixmap(bis_w);leb[5]->setPixmap(bis_w);
	leb[3]->setPixmap(que_w);leb[4]->setPixmap(kin_w);

	leb[63]->setPixmap(rok_b);leb[56]->setPixmap(rok_b);
	leb[62]->setPixmap(nit_b);leb[57]->setPixmap(nit_b);
	leb[61]->setPixmap(bis_b);leb[58]->setPixmap(bis_b);
	leb[59]->setPixmap(que_b);leb[60]->setPixmap(kin_b);

	ui->pro_usr->setPixmap(prof);
	ui->pro_stk->setPixmap(stk);

	for(i=8;i<16;i++)
	{
		leb[i]->setPixmap(pwn_w);
		leb[i+40]->setPixmap(pwn_b);
	}
}

BoardUI::~BoardUI()
{
    delete ui;
}
