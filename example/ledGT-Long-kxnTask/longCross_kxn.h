#ifndef longCross__H
#define longCross__H
#include "kxnTask.h"
#include "longBlink.h"

DEFINE_TASK_STATE(longCross) //thu vien "kxnTask.h"
{
  longCross_ON_R,  //sang den do
  longCross_ON_Y,  //sang den vang
  longCross_ON_G,  //sang den xanh
  longCross_ON_Y1,  //bien dem
  longCross_ON_G1,  //bien dem
  longCross_OFF
};

CREATE_TASK(longCross)
//Khai bao bien cau hinh chan cot den
uint8_t pinG; //den xanh
uint8_t pinY; //den vang
uint8_t pinR; //den do
//Khai bao bien chua thoi gian sang cua tung den
unsigned long timeON_G; //den xanh
unsigned long timeON_Y; //den vang
unsigned long timeON_R; //den do [timeON_R = timeON_G + timeON_Y]

longBlink *slowLight;   //tao bien slowLight tro toi class longBlink
//muc dich, chi can thay doi so thoi gian sang/tat trong che do Blink, thi che do Cross tu dong bo thoi gian theo

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

void setup1(unsigned long timeON_G_, unsigned long timeON_Y_) //tao khung de dien so thoi gian muon den sang
{ 
  timeON_G = timeON_G_;
  timeON_Y = timeON_Y_;
  timeON_R = timeON_G + timeON_Y;
  pinMode(pinG, OUTPUT); pinMode(pinY, OUTPUT); pinMode(pinR, OUTPUT);
}

void setup(unsigned long timeON_G_, unsigned long timeON_Y_, longBlink *pa_slowLight) //tao khung de dien so thoi gian muon den sang
{
  setup1(timeON_G_, timeON_Y_);
  slowLight = pa_slowLight;
}

void loop()
{
  switch(getState())  //xanh -> vang -> do -> xanh1 -> vang1
  {
    case longCross_ON_G:
      Green();
      setState(longCross_ON_Y); //chuyen sang case bat den vang
      kDelay(timeON_G);  //them vao thoi gian sang den
    break;

    case longCross_ON_Y:
      Yellow();
      setState(longCross_ON_R); //chuyen sang case bat den do
      kDelay(timeON_Y);  //them vao thoi gian sang den
    break;

    case longCross_ON_R:
      Red();
      setState(longCross_ON_G1); //chuyen sang case bat den xanh1
      kDelay(timeON_R);  //them vao thoi gian sang den
    break;
    
    case longCross_ON_G1:
      Green();
      setState(longCross_ON_Y1); //chuyen sang case bat den vang1
      kDelay(timeON_G);  //them vao thoi gian sang den
    break;

    // case longCross_ON_Y1:
    //   Yellow();
    //   setState(longCross_OFF); //chuyen sang case bat den do
    //   kDelay(timeON_Y);  //them vao thoi gian sang den
    // break;

    // case longCross_OFF:
    //   this->stop();
    //   setState(longCross_ON_Y1);
    //   kDelay(timeON_Y);  //them vao thoi gian sang den
    // break;

    case longCross_ON_Y1:
      slowLight->start();
      //stop();
    break;
  }
}

//Ham dieu khien chinh
  void start()
  {
    setState(longCross_ON_G);
    kxnTaskManager.add(this); //them vao kxnTaskManager de quan ly
  }

//Tat che do nguoi di bo bang qua duong
void stop() //tat toan bo den
{
  digitalWrite(pinR, LOW);
  digitalWrite(pinY, LOW);
  digitalWrite(pinG, LOW);
  kDelay(0); //huy bo thoi gian sang den
  slowLight->stop();
  setStateIdle();   //dat ve trang thai nhan roi
}

END
#endif