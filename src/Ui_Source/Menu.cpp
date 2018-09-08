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


#include "Ui_Moc/Menu.h"
string image_path = ros::package::getPath("chess_bot");

Menu::Menu(ros::NodeHandle _nh, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Menu), nh(_nh)
{
	ui->setupUi(this);
	logo_pixmap.load((image_path+"/utils/chess_logo.jpg").c_str());
	ui->logo->setPixmap(logo_pixmap);
	set_tab = nh.advertise<std_msgs::Int32>("menu_data", 1000);
}

void Menu::on_newgame_clicked()
{
	tab_flg.data=1;
	set_tab.publish(tab_flg);
}

void Menu::on_gamelist_clicked()
{
	tab_flg.data=2;
	set_tab.publish(tab_flg);
}

void Menu::on_record_clicked()
{
	tab_flg.data=3;
	set_tab.publish(tab_flg);
}

void Menu::on_instr_clicked()
{
	tab_flg.data=4;
	set_tab.publish(tab_flg);
}

void Menu::on_credits_clicked()
{
	tab_flg.data=5;
	set_tab.publish(tab_flg);
}

Menu::~Menu()
{
    delete ui;
}
