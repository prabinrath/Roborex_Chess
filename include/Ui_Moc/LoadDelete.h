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


#ifndef LOADDELETE_H
#define LOADDELETE_H

#include <QMainWindow>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QFrame>
#include <QDebug>
#include <ros/ros.h>
#include <ros/package.h>
#include <fstream>
#include <string>
#include "GameTile.h"
#include "ui_LoadDelete.h"
#include "chess_bot/feature.h"
using namespace std;

namespace Ui {
class LoadDelete;
}

class LoadDelete : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoadDelete(ros::NodeHandle _nh,QWidget *parent = 0);
    void setScrollArea(const chess_bot::feature::ConstPtr& msg);
    void loadTiles();
    ~LoadDelete();
    
private:
    Ui::LoadDelete *ui;
    ros::NodeHandle nh;
    ros::Subscriber sub;
};

#endif // LOADDELETE_H
