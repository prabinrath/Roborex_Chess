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


#ifndef GAMETABS_H
#define GAMETABS_H

#include <QMainWindow>
#include <ros/ros.h>
#include "ui_About.h"
#include "ui_LoadDelete.h"
#include "ui_Menu.h"
#include "ui_NewGame.h"
#include "ui_GameTile.h"

namespace Ui {
class About;
class LoadDelete;
class Menu;
class NewGame;
class GameTile;
}

class About : public QMainWindow
{
    Q_OBJECT

public:
    explicit About(ros::NodeHandle _nh,QWidget *parent = 0);
    ~About();
    
private:
    Ui::About *ui;
    ros::NodeHandle nh;
};


class LoadDelete : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoadDelete(ros::NodeHandle _nh,QWidget *parent = 0);
    ~LoadDelete();
    
private:
    Ui::LoadDelete *ui;
    ros::NodeHandle nh;
};


class Menu : public QMainWindow
{
    Q_OBJECT

public:
    explicit Menu(ros::NodeHandle _nh,QWidget *parent = 0);
    ~Menu();
    
private:
    Ui::Menu *ui;
    ros::NodeHandle nh;
};


class NewGame : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewGame(ros::NodeHandle _nh,QWidget *parent = 0);
    ~NewGame();
    
private:
    Ui::NewGame *ui;
    ros::NodeHandle nh;
};


class GameTile : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameTile(ros::NodeHandle _nh,QWidget *parent = 0);
    ~GameTile();
    
private:
    Ui::GameTile *ui;
    ros::NodeHandle nh;
};
#endif // GAMETABS_H
