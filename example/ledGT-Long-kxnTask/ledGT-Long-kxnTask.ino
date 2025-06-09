/*
  Y tuong: Dieu khien den giao thong thong qua Serial Monitor (Noline Ending)
    - '0': Tat toan bo led
    - '1': Chuyen den cho nguoi di bo qua duong
    - '2': Nhay den vang canh bao 1 giay sang 1 giay tat
    - '3': Cot den hoat dong voi 3 den luan phien
    - '4': Giu nguyen tinh trang den de xe uu tien di qua #1 R1-G2
    - '5': Giu nguyen tinh trang den de xe uu tien di qua #2 G1-R2
    - '6': Doc trang thai den va "tra ve case 3"
  Phan nhiem vu cac file
    - "ledGT-Long-kxnTask.ino": file nhan yeu cau tu nguoi dung --> kiem tra trang thai he thong --> ra lenh thuc hien yeu cau
    - "longDK.h": file nhan lenh tu file "ledGT-Long-kxnTask.ino", thuc hien nhiem vu - bat/tat cac che do, lay tu 2 file con lai
    - "longDK.h": Thay doi thoi gian sang/tat cua che do nhay den vang tai ham setup()
    - "longDK.h": Thay doi thoi gian sang cua den xanh, den vang va suy ra den do tai ham setup()
    - "longDK.h": Thay doi chan ket noi voi con den tai ham setup()
    - "longBlink.h": file quy dinh cac cong viec can thuc hien trong che do nhay den vang
    - "longGT.h": file quy dinh cac cong viec can thuc hien trong che do sang 3 den
  So do noi day
    Cot den 1
      - G1 = 8
      - Y1 = 7
      - R1 = 6
    Cot den 2
      - G2 = 5
      - Y2 = 4
      - R2 = 3

*/

#include "longDK.h"
//Khai bao bien thuoc class longDK
longDK longDK1;

void setup()
{
  Serial.begin(115200);
  longDK1.setup(); 
}
  
void loop()
{
  kxnTaskManager.run(millis());  //kiem tra idle
  checkSerial();  //kiem tra gia tri nguoi dung nhap vao o Serial Monitor
}

void checkSerial()  //Dinh nghia lenh kiem tra gia tri
{
  if(Serial.available())    //ham co san cua Arduino. tuong tu nhu Serial.begin()
  {
    char tt = Serial.read();  //kieu bien char - character = ky tu don
    switch(tt)  //switch_case_break (co example trong muc control cua Arduino)
    {
      case '0':
        longDK1.stopALL(); 
        Serial.println("OFF");
      break;  //ket thuc 1 case
      
      case '1':
        longDK1.cross();
        Serial.println("longCross running");
      break;

      case '2':
        if(longDK1.isBlinkYellowColor_Idle()) 
        {
          longDK1.startBlinkYellowColor();
          Serial.println("longBlink running"); 
        }
      break;  
      
      case '3':
        if(longDK1.isThreeColor_Idle())
        {
          longDK1.startThreeColor();
        }
      break; 
    
      case '4':
        longDK1.urgent4();
      break;  

      case '5':
        longDK1.urgent5();
      break;

      case '6':
        longDK1.startThreeColor1();
      break;
    }
  }
}
  

