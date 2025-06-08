#ifndef longDK__H
#define longDK__H
#include "kxnTask.h"
#include "longBlink.h"
#include "longGT.h"

DEFINE_TASK_STATE(longDK) //thu vien "kxnTask.h"
{longDK_STATE_NOTHING};  //Day la file quan ly cap trung, nen khong co xet trang thai

CREATE_TASK(longDK)   //thu vien "kxnTask.h"
//Khai bao bien thuc hien che do sang 3 den cot den 1 va cot den 2
longGT longGT1, longGT2;
//Khai bao bien thuc hien che do nhay den vang cot den 1 va cot den 2
longBlink longBlinkY1, longBlinkY2;

void setup()
{
  //chinh sua cot den 1 va cot den 2 tai day
    longGT1.setPin1(8, 7, 6); //xanh, vang, do
    longGT1.setup(3000, 1000); //sang den xanh 3000ms, sang den vang 1000ms
    longGT2.setPin2(5, 4, 3); //xanh, vang, do
    longGT2.setup(3000, 1000); //sang den xanh 3000ms, sang den vang 1000ms
    //longGT2.startG(); //bat den xanh ngay sau khi nap chuong trinh
  //chinh sua thoi gian nhay cua cot den 1 va cot den 2 tai day
    longBlinkY1.setup(7, 1000, 1000); //cu phap: (pin, timeON, timeOFF)
    longBlinkY2.setup(4, 1000, 1000); //cu phap: (pin, timeON, timeOFF)
    //duoc cau hinh tu class longBlink
  this->startThreeColor(); //tro den ham startThreeColor() cua file "longDK.h" 
  //--> bat dau che do sang 3 den ngay sau khi nap chuong trinh
}

void startThreeColor()
{
  //lap lai lenh nay tu ham setup() de khi chuyen doi cac che do, he thong van hoat dong theo yeu cau
  longGT1.startR();
  longGT2.startG();
  longBlinkY1.stop();
  longBlinkY2.stop();
  kxnTaskManager.add(this); //them vao kxnTaskManager de quan ly
}

void startBlinkYellowColor()
{
  longGT1.stop();
  longGT2.stop();
  longBlinkY1.start();
  longBlinkY2.start();
  kxnTaskManager.add(this); //them vao kxnTaskManager de quan ly
}


//Khai bao bien kiem tra trang thai nhan roi cua che do sang 3 den va che do nhay den vang canh bao
  //Che do sang 3 den
  uint8_t isThreeColor_Idle()
  {
    if(longGT1.isStateIdle() && longGT2.isStateIdle())   //thu vien "kxnTask.h"
    {
      return true; //neu Che do sang 3 den dang nhan roi, tra ve gia tri true = 1
    }
    return false; //neu Che do sang 3 den khong nhan roi, tra ve gia tri false = 0
  }

  //Che do nhay den vang
  uint8_t isBlinkYellowColor_Idle()
  {
    if(longBlinkY1.isStateIdle() && longBlinkY2.isStateIdle())   //thu vien "kxnTask.h"
    {
      return true;  //neu Che do nhay den vang dang nhan roi, tra ve gia tri true = 1
    }
    return false; //neu Che do nhay den vang dang nhan roi, tra ve gia tri false = 0
  }

void stop() //ham tat toan bo den, hay tat 2 che do
{
  longGT1.stop();
  longBlinkY1.stop();
  longGT2.stop();
  longBlinkY2.stop();
  setStateIdle();   //thu vien "kxnTask.h" --> dat ve trang thai nhan roi
}

END
#endif