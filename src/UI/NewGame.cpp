#include "NewGame.h"
#include "ui_NewGame.h"

NewGame::NewGame(ros::NodeHandle _nh, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewGame), nh(_nh)
{
	ui->setupUi(this);
}

NewGame::~NewGame()
{
    delete ui;
}