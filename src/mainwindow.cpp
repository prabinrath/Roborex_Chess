#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <pthread.h>

int swh,mv_cnt=0; //swh=flag to switch between messages types of airecv suscriber,mv_cnt=the move counter
bool master=false,pub_cntrl=false,dstr=false; //master=turn flag for the ui node ,pub_cntrl=publishing control
QString indat;

void *ROS_task(void *q)
	{
	ros::NodeHandle h;
	ros::Publisher aisend;
	aisend = h.advertise<chess_bot::ui_data>("ui_recv", 1000);
	ros::Rate loop_rate(30);
	while(ros::ok() && dstr==false)
   	{
    	if(pub_cntrl==true)
	{
		chess_bot::ui_data toui;
		toui.type=swh;
		if(swh==0 || swh==2)
		{
			toui.sys=indat.toStdString();
		}
		aisend.publish(toui);
		pub_cntrl=false;
	}
    	loop_rate.sleep();
    	ros::spinOnce();
   	}
	pthread_exit(NULL);
	}

MainWindow::MainWindow(ros::NodeHandle _nh, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), nh(_nh)
{
	ui->setupUi(this);
	setboard();
	airecv = nh.subscribe("ui_send", 10, &MainWindow::callback, this);
	turn = nh.subscribe("turn_flag", 10, &MainWindow::setflag, this);

	pthread_t thread;
	int rc;
	rc=pthread_create(&thread,NULL,ROS_task,(void *)master);
	if(rc)
	{
	ROS_INFO("Error %d",rc);
	exit(-1);
	}
}

void MainWindow::on_send_clicked()
{
	indat=ui->sys_in->toPlainText();
	ui->sysout->setText(QString("SYSTEM OUTPUT"));
	pub_cntrl=true;
}

void MainWindow::setflag(const std_msgs::Bool::ConstPtr& msg)
{
	master=msg->data;
}

void MainWindow::callback(const chess_bot::ui_data::ConstPtr& msg)
{
	swh=msg->type;
	if(swh!=4)
	{ui->sysout->setText(QString(msg->sys.c_str()));}
	else
	{
	if(master==false)
	{
		ui->move->setItem(mv_cnt, 0, new QTableWidgetItem(QString(ui->usr_name->text())));
		ui->move->setItem(mv_cnt, 1, new QTableWidgetItem(QString(msg->mo.c_str())));
	}
	else
	{
		ui->move->setItem(mv_cnt, 0, new QTableWidgetItem("stockfish"));
		ui->move->setItem(mv_cnt, 1, new QTableWidgetItem(QString(msg->mo.c_str())));
	}
	mv_cnt++;
	}
}

void MainWindow::setboard()
{
	ui->move->setRowCount(100);
	ui->move->setStyleSheet("QTableView {selection-background-color: rgb(255,228,181);}");
}

MainWindow::~MainWindow()
{
    dstr=true;
    delete ui;
}
