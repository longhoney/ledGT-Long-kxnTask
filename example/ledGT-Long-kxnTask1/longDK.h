#ifndef longDK__H
#define longDK__H
#include "kxnTask.h"
#include "longBlink.h"
#include "longGT.h"

DEFINE_TASK_STATE(longDK) //thu vien "kxnTask.h"
{longDK_STATE_NOTHING};  //Day la file quan ly cap trung, nen khong co xet trang thai

CREATE_TASK(longDK)   //thu vien "kxnTask.h"
//Khai bao bien
  //Che do nhay den vang
  longBlink longBlinkY1, longBlinkY2;
  //Che do den giao thong sang 3 den tuan tu
  longGT longGT1, longGT2;

void setup()  //chinh sua cot den 1 va cot den 2 tai day
{
  Serial.begin(115200);
  //Che do 3 den
    longGT1.setPin1(8, 7, 6); //xanh, vang, do
    longGT2.setPin2(5, 4, 3);
    longGT1.setup(3000, 1000); //sang den xanh 3000ms, sang den vang 1000ms
    longGT2.setup(3000, 1000);
  //Che do nhay den vang
    longBlinkY1.setup(7, 2000, 2000); //cu phap: (pin, timeON, timeOFF)
    longBlinkY2.setup(4, 2000, 2000); //cu phap: (pin, timeON, timeOFF)
  //tro den ham startThreeColor() cua file "longDK.h" 
    this->startThreeColor();
      //--> bat dau che do sang 3 den ngay sau khi nap chuong trinh
      //--> bo lenh nay de tat toan bo den sau khi nap chuong trinh
}

//Ham tat den - case '0'
  void stopALL()
  {
    longGT1.stop(); //tat giao thong
    longGT2.stop();
    longBlinkY2.stop(); //tat nhay
    longBlinkY1.stop();
    setStateIdle();   //thu vien "kxnTask.h" --> dat ve trang thai nhan roi
  }

//Ham nhay den vang - case '2'
  void startBlinkYellowColor()
  {
    stopALL();
    longBlinkY1.start();
    longBlinkY2.start();
    kxnTaskManager.add(this); 
  }

//Ham den giao thong - case '3'
  void startThreeColor()
  {
    stopALL();
    longGT1.startR();
    longGT2.startG();
    kxnTaskManager.add(this); 
  }

//Khai bao bien kiem tra trang thai nhan roi
  //Che do sang 3 den
    uint8_t isThreeColor_Idle()
    {
      if(longGT1.isStateIdle() && longGT2.isStateIdle())  
      {
        return true; //neu Che do sang 3 den dang nhan roi, tra ve gia tri true = 1
      }
      return false; //neu Che do sang 3 den khong nhan roi, tra ve gia tri false = 0
    }

  //Che do nhay den vang
    uint8_t isBlinkYellowColor_Idle()
    {
      if(longBlinkY1.isStateIdle() && longBlinkY2.isStateIdle())  
      {
        return true;  
      }
      return false;
    }

END
#endif