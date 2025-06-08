#ifndef longGT__H
#define longGT__H
#include "kxnTask.h"

DEFINE_TASK_STATE(longGT) //thu vien "kxnTask.h"
{
  longGT_ON_R,  //sang den do
  longGT_ON_Y,  //sang den vang
  longGT_ON_G,  //sang den xanh
};

CREATE_TASK(longGT)
//Khai bao bien cau hinh chan cot den
uint8_t pinG; //den xanh
uint8_t pinY; //den vang
uint8_t pinR; //den do
//Khai bao bien chua thoi gian sang cua tung den
unsigned long timeON_G; //den xanh
unsigned long timeON_Y; //den vang
unsigned long timeON_R; //den do [timeON_R = timeON_G + timeON_Y]

//Ham setPin() de cau hinh chan cho cot den 1
void setPin1(uint8_t pin_G, uint8_t pin_Y, uint8_t pin_R)
{
  this->pinG = pin_G;
  this->pinY = pin_Y;
  this->pinR = pin_R;
}

//Ham setPin() de cau hinh chan cho cot den 2
void setPin2(uint8_t pin__G, uint8_t pin__Y, uint8_t pin__R)
{
  this->pinG = pin__G;
  this->pinY = pin__Y;
  this->pinR = pin__R;
}


void setup(unsigned long timeON_G_, unsigned long timeON_Y_) //tao khung de dien so thoi gian muon den sang
{ 
  timeON_G = timeON_G_;
  timeON_Y = timeON_Y_;
  timeON_R = timeON_G + timeON_Y;
  pinMode(pinG, OUTPUT); pinMode(pinY, OUTPUT); pinMode(pinR, OUTPUT);
}

void loop()
{
  //switch_case_break
  switch (getState()) //thu vien "kxnTask.h"
  {
    case longGT_ON_R: //bat den do
      Red();
      setState(longGT_ON_G); //chuyen sang case bat den xanh
      kDelay(timeON_R);  //them vao thoi gian sang den
    break;
    case longGT_ON_G: //bat den xanh
      Green();
      setState(longGT_ON_Y);  //chuyen sang case bat den vang
      kDelay(timeON_G);  //them vao thoi gian sang den
    break;
    case longGT_ON_Y: //bat den vang
      Yellow();
      setState(longGT_ON_R);  //tro lai case bat den do
      kDelay(timeON_Y); //them vao thoi gian sang den
    break;
  }
}

//Phim tat bat den
  void Green()
  {
    digitalWrite(pinR, LOW);
    digitalWrite(pinY, LOW);
    digitalWrite(pinG, HIGH);
  }

  void Yellow()
  {
    digitalWrite(pinR, LOW);
    digitalWrite(pinY, HIGH);
    digitalWrite(pinG, LOW);
  }

  void Red()
  {
    digitalWrite(pinR, HIGH);
    digitalWrite(pinY, LOW);
    digitalWrite(pinG, LOW);
  }
//Cau hinh ham dung trong file longDK
  void startR() //ham bat den do
  {
    setState(longGT_ON_R); //goi tu trong switch_case_break
    kxnTaskManager.add(this); //them vao kxnTaskManager de quan ly
  }

  void startY() //ham bat den vang
  {
    setState(longGT_ON_Y); //goi tu trong switch_case_break
    kxnTaskManager.add(this); //them vao kxnTaskManager de quan ly
  }

  void startG() //ham bat den xanh
  {
    setState(longGT_ON_G); //goi tu trong switch_case_break
    kxnTaskManager.add(this); //them vao kxnTaskManager de quan ly
  }
//Cau hinh cho tinh huong nguoi di bo bang qua duong


void stop() //tat toan bo den
{
  digitalWrite(pinR, LOW);
  digitalWrite(pinY, LOW);
  digitalWrite(pinG, LOW);
  kDelay(0); //huy bo thoi gian sang den
  setStateIdle();   //dat ve trang thai nhan roi
}

END
#endif