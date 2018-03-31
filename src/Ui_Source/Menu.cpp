#include "Ui_Moc/Menu.h"

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
