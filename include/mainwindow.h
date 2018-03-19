#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <QString>
#include "chess_bot/ui_data.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(ros::NodeHandle _nh,QWidget *parent = 0);
    ~MainWindow();
    void setboard();
    void setflag(const std_msgs::Bool::ConstPtr& msg);
    void callback(const chess_bot::ui_data::ConstPtr& msg);
private slots:
	void on_send_clicked();

private:
    Ui::MainWindow *ui;
    ros::NodeHandle nh;
    ros::Subscriber airecv;
    ros::Subscriber turn;
};

#endif // MAINWINDOW_H
