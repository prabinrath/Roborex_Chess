#include "About.h"
#include "ui_About.h"

About::About(ros::NodeHandle _nh, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::About), nh(_nh)
{
	ui->setupUi(this);
}

About::~About()
{
    delete ui;
}
