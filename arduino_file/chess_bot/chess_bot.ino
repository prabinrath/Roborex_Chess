//ROBOREX_CHESS_MATE Arduino Node
#include <EnableInterrupt.h>

#define x_offset
#define y_offset
#define x_mv
#define y_mv

unsigned long prev_send=0,curr_send;
boolean send_flag=false;
int cnt=0;

int ir_pin=2;
int ir_pin_2=3;

#include <ros.h>
#include <std_msgs/String.h>

ros::NodeHandle  nh;

std_msgs::String debg;
boolean flag=false,turn=false;
String movedat="";

ros::Publisher pub_d("user_swh", &debg);//debugging for arduino

void callback( const std_msgs::String& msg) //callback function for stockfish onboard move
{
 String mv=msg.data;
 if(mv=="ok")
 {
  flag=true;
 }
 else if(mv[0]=='1' || mv[0]=='2')
 {
   mv.replace("1_","");
   mv.replace("2_","");
   movedat+=mv;
 }
}

ros::Subscriber<std_msgs::String> sub("move_seq", &callback );//suscriber of stockfish move from chess_ai

void confirm()
{
  movedat="ok";
  flag=true;
}

void camera_feed()
{
  movedat="n";
  flag=true;  
}

void setup()
{ 
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  pinMode(ir_pin, INPUT);pinMode(ir_pin_2, INPUT);
  enableInterrupt(A0,confirm,RISING);
  enableInterrupt(A1,camera_feed,RISING);
  //attachInterrupt(digitalPinToInterrupt(ir_pin),confirm, RISING);
  //attachInterrupt(digitalPinToInterrupt(ir_pin_2),camera_feed, RISING);
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(pub_d);
}

void loop()
{ 
   if(flag==true)
   {
     debg.data=movedat.c_str();
     pub_d.publish(&debg);flag=false;
     movedat="";
   }
  nh.spinOnce();
}

