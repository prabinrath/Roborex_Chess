#ifndef BOARDUI_H
#define BOARDUI_H

#include <QMainWindow>
#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <QLabel>
#include <QPixmap>
#include <QString>
#include <std_msgs/String.h>

namespace Ui {
class BoardUI;
}

class BoardUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit BoardUI(ros::NodeHandle _nh,QWidget *parent = 0);
    ~BoardUI();
    void setboard();
    void callback(const std_msgs::String::ConstPtr& msg);
    void setflag(const std_msgs::Bool::ConstPtr& msg);
    void setfen(QString fen);
    QLabel *leb[64];
    QPixmap kin_w,que_w,nit_w,bis_w,rok_w,pwn_w,kin_b,que_b,nit_b,bis_b,rok_b,pwn_b,chnc,prof,stk,blnk;

private:
    Ui::BoardUI *ui;
    ros::NodeHandle nh;
    ros::Subscriber sub;
    ros::Subscriber turn;
};

#endif // BOARDUI_H
