#include "Ui_Moc/MainUI.h"

MainUI::MainUI(ros::NodeHandle _nh, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainUI), nh(_nh)
{
	ui->setupUi(this);
}

MainUI::~MainUI()
{
    delete ui;
}
