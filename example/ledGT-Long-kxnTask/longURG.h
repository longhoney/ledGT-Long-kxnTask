#ifndef longURG__H
#define longURG__H
#include "kxnTask.h"

DEFINE_TASK_STATE(longURG)
{
  longURG_READ_PRINT, longURG_READ_PRINT1,
  longURG_HOLD, longURG_HOLD1
};

CREATE_TASK(longURG)
//Khai bao bien doc tin hieu tu chan den
uint8_t pinG1; uint8_t pinY1; uint8_t pinR1;
uint8_t pinG2; uint8_t pinY2; uint8_t pinR2;

//Ham setPin() de cau hinh chan cho cot den 1
void setPin1(uint8_t pin_G, uint8_t pin_Y, uint8_t pin_R)
{
  this->pinG1 = pin_G;
  this->pinY1 = pin_Y;
  this->pinR1 = pin_R;
}

//Ham setPin() de cau hinh chan cho cot den 2
void setPin2(uint8_t pin__G, uint8_t pin__Y, uint8_t pin__R)
{
  this->pinG2 = pin__G;
  this->pinY2 = pin__Y;
  this->pinR2 = pin__R;
}

void setup()
{
  pinMode(pinG1, OUTPUT); pinMode(pinY1, OUTPUT); pinMode(pinR1, OUTPUT);
  pinMode(pinG2, OUTPUT); pinMode(pinY2, OUTPUT); pinMode(pinR2, OUTPUT);
}

void ReadPrint()
{
  int G1State = digitalRead(pinG1); int Y1State = digitalRead(pinY1); int R1State = digitalRead(pinR1);
  int G2State = digitalRead(pinG2); int Y2State = digitalRead(pinY2); int R2State = digitalRead(pinR2);
  Serial.print("R1State: ");
  Serial.println(R1State);
  Serial.print("R2State: ");
  Serial.println(R2State);
}

void loop()
{
  switch(getState())
  {
    case longURG_READ_PRINT:
      ReadPrint();
      setState(longURG_HOLD);
    break;
    case longURG_HOLD:
      digitalWrite(pinR1, HIGH); //giu nguyen do 1
      digitalWrite(pinG2, HIGH); //giu nguyen xanh 2
      setState(longURG_READ_PRINT);
    break;
    case longURG_READ_PRINT1:
      ReadPrint();
      setState(longURG_HOLD1);
    break;
    case longURG_HOLD1:
      digitalWrite(pinG1, HIGH); //giu nguyen xanh 1
      digitalWrite(pinR2, HIGH); //giu nguyen do 2
      setState(longURG_READ_PRINT1);
    break;
  }
}

void urg4()
{
  setState(longURG_READ_PRINT);
  kxnTaskManager.add(this); //them vao kxnTaskManager de quan ly
}

void urg5()
{
  setState(longURG_READ_PRINT1);
  kxnTaskManager.add(this); //them vao kxnTaskManager de quan ly
}

void stop()
{
  digitalWrite(pinR1, LOW); 
  digitalWrite(pinG2, LOW);
  setStateIdle();   //dat ve trang thai nhan roi
}

END
#endif