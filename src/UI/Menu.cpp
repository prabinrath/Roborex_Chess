#include "Menu.h"
#include "ui_Menu.h"

Menu::Menu(ros::NodeHandle _nh, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Menu), nh(_nh)
{
	ui->setupUi(this);
}

Menu::~Menu()
{
    delete ui;
}
