#include "GameTile.h"
#include "ui_GameTile.h"

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
