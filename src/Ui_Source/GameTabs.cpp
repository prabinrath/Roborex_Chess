#include "Ui_Moc/GameTabs.h"

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
