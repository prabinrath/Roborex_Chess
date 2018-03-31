#include "Ui_Moc/GameTile.h"

GameTile::GameTile(ros::NodeHandle _nh, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameTile), nh(_nh)
{
	ui->setupUi(this);
}

GameTile::~GameTile()
{
    delete ui;
}
