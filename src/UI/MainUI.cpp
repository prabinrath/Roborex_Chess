#include "MainUI.h"
#include "ui_MainUI.h"

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
