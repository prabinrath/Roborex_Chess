#include "Stepper.h"
#include"string.h"
#define box_length 8

int ir_pin_x=2,ir_pin_y=3;
int counter=0;

unsigned long previous=0,current;
const int stepsPerRevolution=200;

Stepper x_(stepsPerRevolution,4,5,6,7);
Stepper y_(stepsPerRevolution,11,10,9,8);

void setup() 
{
  y_.setSpeed(10);
  x_.setSpeed(10); 
  
  pinMode(ir_pin_y, INPUT);
  pinMode(ir_pin_x, INPUT);
  
  pinMode(A0,OUTPUT);
  Serial.begin(9600);
  
  attachInterrupt(digitalPinToInterrupt(ir_pin_y),IRQcounter, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ir_pin_x),IRQcounter, CHANGE);
  
  digitalWrite(A0,LOW);
  delay(1000);
}

void IRQcounter()
{
  current=millis();
  if(current-previous>70)
    {
      counter++;
      //Serial.println(counter);
    }
  previous=current;  
}

void _move(char slider,char sense,int task)
{
  Serial.print("Here");Serial.print(sense);Serial.println(task);
   counter=0;
   if(slider=='y')
   {
    while(counter<task*box_length)
    {
      if(sense=='0')
        {y_.step(1);}
      else if(sense=='1')
        {y_.step(-1);}
      Serial.println(counter);
    }
   }
   else if(slider=='x')
   {
     while(counter<task*box_length)
    {
      if(sense=='1')
        {x_.step(1);}
      else if(sense=='0')
        {x_.step(-1);}
      Serial.println(counter);
    }
   }     
}

//y10x11y50x11Hx10y41x11Ly11x10y11x10 (e2e4 normal)
void loop() 
{
  String steps="";
  if(Serial.available())
  {
    steps=Serial.readString();
    Serial.println(steps);

    int l=0;
    while(l<steps.length())
    {
      if(steps[l]=='y' || steps[l]=='x')
      {
        char select=steps[l];
        String temp="";l++;
        while(isDigit(steps[l]))
        {temp+=steps[l];l++;}
        l--;
        char sense=temp[temp.length()-1];
        temp.remove(temp.length()-1);Serial.println(temp);
        _move(select,sense,temp.toInt());
        delay(200);
      }
      else if(steps[l]=='H')
      {digitalWrite(A0,HIGH);delay(2000);Serial.println(steps[l]);}
      else if(steps[l]=='L')
      {digitalWrite(A0,LOW);delay(2000);Serial.println(steps[l]);}
      l++;
    }
  }
}
