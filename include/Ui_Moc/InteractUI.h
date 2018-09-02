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


#ifndef INTERACTUI_H
#define INTERACTUI_H

#include <QMainWindow>
#include <QMessageBox>
#include <QCloseEvent>
#include <QString>
#include <QDebug>
#include <stdio.h>
#include <fstream>
#include <string>
#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Int32.h>
#include <ros/package.h>
#include "ui_InteractUI.h"
#include "chess_bot/feature.h"
#include "chess_bot/ui_data.h"
//#include "BoardUI.h"
using namespace std;

namespace Ui {
class InteractUI;
}

class InteractUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit InteractUI(ros::NodeHandle _nh,QWidget *parent = 0);
    ~InteractUI();
    void setUI();
    void closeEvent(QCloseEvent *event);
    void setflag(const std_msgs::Bool::ConstPtr& msg);
    void ui_callback(const chess_bot::ui_data::ConstPtr& msg);
private slots:
	void on_send_clicked();
	void on_save_clicked();
	void on_undo_clicked();
	void on_rst_clicked();

private:
	int swh,mv_cnt; //swh=flag to switch between messages types of airecv suscriber,mv_cnt=the move counter
	bool master,save_flag; //master=turn flag for the ui node ,pub_cntrl=publishing control
	string user_name;
    Ui::InteractUI *ui;
    ros::NodeHandle nh;
    ros::Publisher aisend,interact,close_ui_flag;
    ros::Subscriber airecv,turn;
     //BoardUI *handle;
};

#endif // INTERACTUI_H
