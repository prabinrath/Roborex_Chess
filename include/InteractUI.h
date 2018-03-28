#ifndef INTERACTUI_H
#define INTERACTUI_H

#include <QMainWindow>
#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <QString>
#include "chess_bot/ui_data.h"
//#include "BoardUI.h"

namespace Ui {
class InteractUI;
}

class InteractUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit InteractUI(ros::NodeHandle _nh,QWidget *parent = 0);
    ~InteractUI();
    void setUI();
    void setflag(const std_msgs::Bool::ConstPtr& msg);
    void callback(const chess_bot::ui_data::ConstPtr& msg);
private slots:
	void on_send_clicked();

private:
    Ui::InteractUI *ui;
    //BoardUI *handle;
    ros::NodeHandle nh;
    ros::Subscriber airecv;
    ros::Subscriber turn;
};

#endif // INTERACTUI_H
