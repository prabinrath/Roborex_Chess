#include "Ui_Moc/LoadDelete.h"

LoadDelete::LoadDelete(ros::NodeHandle _nh, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoadDelete), nh(_nh)
{
	ui->setupUi(this);
}

LoadDelete::~LoadDelete()
{
    delete ui;
}
