#ifndef longDK__H
#define longDK__H
#include "kxnTask.h"
#include "longBlink.h"
#include "longGT.h"
//#include "longCross.h"
#include "longCross_kxn.h"
#include "longURG.h"

DEFINE_TASK_STATE(longDK) //thu vien "kxnTask.h"
{longDK_STATE_NOTHING};  //Day la file quan ly cap trung, nen khong co xet trang thai

CREATE_TASK(longDK)   //thu vien "kxnTask.h"
//Khai bao bien
  //Che do nhay den vang
  longBlink longBlinkY1, longBlinkY2;
  //Che do nguoi di bo bang qua duong
  longCross longCross1, longCross2;
  //Che do giu den xanh cho xe uu tien
  longURG longURG1, longURG2;
  //Che do den giao thong sang 3 den tuan tu
  longGT longGT1, longGT2;
  uint8_t pinR1 = 6; uint8_t pinR2 = 3;

void setup()  //chinh sua cot den 1 va cot den 2 tai day
{
  Serial.begin(115200);
  //Che do 3 den
  longGT1.setPin1(8, 7, 6); //xanh, vang, do
  longGT2.setPin2(5, 4, 3);
  longGT1.setup(3000, 1000); //sang den xanh 3000ms, sang den vang 1000ms
  longGT2.setup(3000, 1000);
  //Che do nguoi di bo bang qua duong
  longCross1.setPin1(8, 7, 6); 
  longCross2.setPin2(5, 4, 3); 
  // longCross1.setup(3000, 1000);
  // longCross2.setup(3000, 1000);
  longCross1.setup(3000, 1000, &longBlinkY1);
  longCross2.setup(3000, 1000, &longBlinkY2);

  //Che do nhay den vang
  longBlinkY1.setup(7, 2000, 2000); //cu phap: (pin, timeON, timeOFF)
  longBlinkY2.setup(4, 2000, 2000); //cu phap: (pin, timeON, timeOFF)
  //Che do giu den xanh cho xe uu tien
  longURG1.setPin1(8, 7, 6);
  longURG2.setPin2(5, 4, 3);
  longURG1.setup();
  longURG2.setup();
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
    longCross1.stop();  //tat bang qua duong
    longCross2.stop();
    longURG1.stop();  //tat giu den xanh cho xe uu tien
    longURG2.stop();
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

//Ham bang qua duong - case '1'
  void cross()
  {
    stopALL();
    longCross1.start();
    longCross2.start();
    kxnTaskManager.add(this); 
  }

//Ham giu xanh cho xe uu tien, duong doc - case '4'
  void urgent4()
  {
    stopALL();
    longURG1.urg4();
    longURG2.urg4();
    kxnTaskManager.add(this); 
  }

//Ham giu xanh cho xe uu tien, duong ngang - case '5'
  void urgent5()
  {
    stopALL();
    longURG1.urg5();
    longURG2.urg5();
    kxnTaskManager.add(this); 
  }

//Ham chuyen ve che do den giao thogn sau khi giu xanh cho xe uu tien
  void startThreeColor1()
  {
    int R1State = digitalRead(pinR1); int R2State = digitalRead(pinR2);
    if(R1State == HIGH) //case '4'
    {
      stopALL();
      longGT1.startR();
      longGT2.startG();
      kxnTaskManager.add(this); 
    }
    if(R2State == HIGH) //case '5'
    {
      stopALL();
      longGT1.startG();
      longGT2.startR();
      kxnTaskManager.add(this); 
    }
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