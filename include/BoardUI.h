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


#ifndef BOARDUI_H
#define BOARDUI_H

#include <QMainWindow>
#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <QLabel>
#include <QPixmap>
#include <QString>
#include <std_msgs/String.h>

namespace Ui {
class BoardUI;
}

class BoardUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit BoardUI(ros::NodeHandle _nh,QWidget *parent = 0);
    ~BoardUI();
    void setboard();
    void callback(const std_msgs::String::ConstPtr& msg);
    void setflag(const std_msgs::Bool::ConstPtr& msg);
    void setfen(QString fen);
    QLabel *leb[64];
    QPixmap kin_w,que_w,nit_w,bis_w,rok_w,pwn_w,kin_b,que_b,nit_b,bis_b,rok_b,pwn_b,chnc,prof,stk,blnk;

private:
    Ui::BoardUI *ui;
    ros::NodeHandle nh;
    ros::Subscriber sub;
    ros::Subscriber turn;
};

#endif // BOARDUI_H
