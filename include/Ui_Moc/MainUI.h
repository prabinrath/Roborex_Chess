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


#ifndef MAINUI_H
#define MAINUI_H

#include <QMainWindow>
#include <QMessageBox>
#include <QProcess>
#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include "Menu.h"
#include "InteractUI.h"
#include "NewGame.h"
#include "LoadDelete.h"
#include "About.h"
#include "ui_MainUI.h"
#include "chess_bot/feature.h"

namespace Ui {
class MainUI;
}

class MainUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainUI(ros::NodeHandle _nh,QWidget *parent = 0);
    void closeEvent(QCloseEvent *event);
    void setUI(const chess_bot::feature::ConstPtr& msg);
    void tabControl(const std_msgs::Int32::ConstPtr& msg);
    ~MainUI();
    
private:
    Ui::MainUI *ui;
    QProcess *boardUI=NULL; //to launch BoardUI
    InteractUI *interactUI=NULL; //to launch InteractUI in a separate window
    ros::NodeHandle nh; 
    chess_bot::feature fetmsg; //for interactions with chess_ai
    ros::Publisher feature_command; //to publish the quit event
    ros::Suscriber set,menu_command; //to connect Menu with main UI
    int menu_flg,newgame_flg,loadgame_flg,record_flg,inst_flg,credit_flg; //flags to prevent ambiguity of multiple UI instances 
};

#endif // MAINUI_H
