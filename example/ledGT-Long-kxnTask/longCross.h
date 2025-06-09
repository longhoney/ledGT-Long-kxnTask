#ifndef longCross__H
#define longCross__H
#include "kxnTask.h"

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

//Ham cau hinh chan cho cot den
  //cot den 1
    void setPin1(uint8_t pin_G, uint8_t pin_Y, uint8_t pin_R)
    {
      this->pinG = pin_G;
      this->pinY = pin_Y;
      this->pinR = pin_R;
    }

  //cot den 2
    void setPin2(uint8_t pin__G, uint8_t pin__Y, uint8_t pin__R)
    {
      this->pinG = pin__G;
      this->pinY = pin__Y;
      this->pinR = pin__R;
    }

//tao khung de dien so thoi gian muon den sang
  void setup(unsigned long timeON_G_, unsigned long timeON_Y_) 
  { 
    timeON_G = timeON_G_;
    timeON_Y = timeON_Y_;
    timeON_R = timeON_G + timeON_Y;
    pinMode(pinG, OUTPUT); pinMode(pinY, OUTPUT); pinMode(pinR, OUTPUT);
  }

//Phim tat bat den
  void Green()
  {
    digitalWrite(pinG, HIGH); digitalWrite(pinY, LOW); digitalWrite(pinR, LOW);
  }

  void Yellow()
  {
    digitalWrite(pinG, LOW); digitalWrite(pinY, HIGH); digitalWrite(pinR, LOW);
  }

  void Red()
  {
    digitalWrite(pinG, LOW); digitalWrite(pinY, LOW); digitalWrite(pinR, HIGH);
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

    case longCross_ON_Y1:
      Yellow();
      setState(longCross_OFF); //chuyen sang case bat den do
      kDelay(timeON_Y);  //them vao thoi gian sang den
    break;

    case longCross_OFF:
      this->stop();
      setState(longCross_ON_Y1);
      kDelay(timeON_Y);  //them vao thoi gian sang den
    break;
  }
}

//Cau hinh ham su dung trong file longDK
  void start() //Chay ham nay khi file longDK thuc hien ham cross()
  {
    setState(longCross_ON_G);
    kxnTaskManager.add(this); //them vao kxnTaskManager de quan ly
  }

  void stop() //Chay ham nay khi file longDK thuc hien ham stopALL()
  {
    digitalWrite(pinR, LOW);
    digitalWrite(pinY, LOW);
    digitalWrite(pinG, LOW);
    kDelay(0); //huy bo thoi gian sang den
    setStateIdle();   //dat ve trang thai nhan roi
  }

END
#endif