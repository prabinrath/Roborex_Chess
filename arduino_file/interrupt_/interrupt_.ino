// for e2e4 normal move y10x11y50x11Hx10y41x11Ly11x10y11x10 
// for e2e4 kill y10x11y10x11Hx10y80x11Lx10y41x11Hx10y41x11Ly11x10y11x10

#include <Stepper.h>
#include<ctype.h>
int ir_pin_y = 3,ir_pin_x=2,i=1; 
int counter = 0;
unsigned long previous=0,current;

const int stepsPerRevolution = 200;
Stepper x_(stepsPerRevolution, 4, 5, 6, 7);
Stepper y_(stepsPerRevolution, 11, 10, 9, 8);

void setup() 
{
  y_.setSpeed(15);
  x_.setSpeed(15);

  pinMode(ir_pin_y, INPUT);
  pinMode(ir_pin_x, INPUT);
  pinMode(12,OUTPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(ir_pin_y),IRQcounter, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ir_pin_x),IRQcounter, CHANGE);
  
  digitalWrite(A0,LOW);
  delay(1000);
}

void IRQcounter()
{
  current=millis();
  if(current-previous>30)
    {
      counter++;
    Serial.println(counter);
    }
  previous=current;
}

String steps="0",s="";
int task=0;

void loop()
{
  if(Serial.available())
    {
      steps=Serial.readString();
      //Serial.println(steps);
      if(steps=="x" || steps=="y")
        s=steps;
      else if(steps=="o")
        digitalWrite(A0,HIGH);
      else if(steps=="f")
        digitalWrite(A0,LOW);
      else 
      {
        task=steps.toInt();
        counter=0;
      }
    }
      if(s=="y")
      {
        if(task>0 && counter<task)
        y_.step(1);
        else if(task<0 && counter<abs(task))
        y_.step(-1);
      }
      else if(s=="x")
      {
        if(task>0 && counter<task)
        x_.step(1);
        else if(task<0 && counter<abs(task))
        x_.step(-1);
      }
}
