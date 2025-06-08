#ifndef longBlink__H
#define longBlink__H
#include "kxnTask.h"

DEFINE_TASK_STATE(longBlink) //thu vien "kxnTask.h"
{longBlink_ON, longBlink_OFF}; //chop, tat

CREATE_TASK(longBlink)
//Khai bao bien
uint8_t pin; //Bien luu gia tri chan ket noi voi den vang
unsigned long timeON; //Bien luu gia tri thoi gian sang den
//unsigned la kieu so nguyen khong am
//long la kieu du lieu su dung nhieu bo nho de luu gia tri
unsigned long timeOFF; //Bien luu gia tri thoi gian tat den

void setup(uint8_t pin_, unsigned long timeON_, unsigned long timeOFF_)  //tao khung de dien so thoi gian muon den sang, chan tin hieu muon su dung
{
  pin = pin_;
  timeON = timeON_;
  timeOFF = timeOFF_;
  pinMode(pin, OUTPUT); //cau hinh chan ket noi voi den vang la OUTPUT
}


void loop()
{
  //switch_case_break
  switch(getState())  //thu vien "kxnTask.h"
  {
    //nhay den
    case longBlink_ON: //ten case dang chuoi ky tu - string nen khong can bo vao nhay don
      digitalWrite(pin, HIGH);
      kDelay(timeON); //them vao thoi gian sang den
      setState(longBlink_OFF);  //chuyen sang case tiep theo, 
      //neu khong se tu thoat khoi switch_case_break
    break;  //ket thuc 1 case
    //tat den
    case longBlink_OFF:  //ten case dang chuoi ky tu - string nen khong can bo vao nhay don
      digitalWrite(pin, LOW);
      kDelay(timeOFF);  //them vao thoi gian tat den
      setState(longBlink_ON); //quay tro lai case ban dau,
      //neu khong se tu thoat khoi switch_case_break
    break; //ket thuc 1 case
    //neu khong phai 2 case tren
    default:  break;  //bo qua, ket thuc 1 case
  }
}

void start()
{
  kxnTaskManager.add(this);
  setState(longBlink_ON);
}

void stop()
{
  digitalWrite(pin, LOW);
  kDelay(0);  //huy bo thoi gian sang/tat
  setStateIdle();
}

void runFast()
{  
  // this function will be called without delay
  Serial.println("longBlink running");
}

END
#endif