/*
  Y tuong: Dieu khien den giao thong thong qua Serial Monitor (Noline Ending)
    - '0': Tat toan bo led
    - '1': Chuyen den cho nguoi di bo qua duong
    - '2': Nhay den vang canh bao 1 giay sang 1 giay tat
    - '3': Cot den hoat dong voi 3 den luan phien
    - '4': Giu nguyen tinh trang den de xe uu tien di qua #1 R1-G2 --> tra ve '3'
    - '5': Giu nguyen tinh trang den de xe uu tien di qua #2 G1-R2 --> tra ve trang thai dem --> ve 3
    - '6': '5' --> trang thai dem --> ve 3 (mot case '3' thu 2, bat dau voi G1-R2)
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
//Khai bao bien moi thuoc class longCtrl
longDK longDK1;
//Cau hinh toc do baudrate de su dung Serial Monitor

void setup()
{
  Serial.begin(115200);
  longDK1.setup();   //Cau hinh bien longDK1 thuoc class longCtrl
}
  
void loop()
{
  //Trong vong loop(), Chay kxnTaskManager de quan ly toan bo he thong den giao thong
  kxnTaskManager.run(millis());   //thu vien "kxnTask.h"
  //chay lenh kiem tra gia tri nguoi dung nhap vao o Serial Monitor
  checkSerial();
}

//Dinh nghia lenh kiem tra gia tri nguoi dung nhap vao o Serial Monitor
void checkSerial()  
{
  if(Serial.available())    //ham co san cua Arduino. tuong tu nhu Serial.begin()
  {
    //luu gia tri nguoi dung nhap vao o Serial Monitor
    char tt = Serial.read();  //kieu bien char - character = ky tu don
    //switch_case_break
    switch(tt) 
    {
      case '0':
        longDK1.stop();   //gui yeu cau den "longDK.h"
        Serial.println("OFF");
      break;  //ket thuc 1 case
      
      case '1':
        longDK1.cross();
      break;

      case '2':
        if(longDK1.isBlinkYellowColor_Idle()) 
        {
          longDK1.startBlinkYellowColor(); //gui yeu cau den "longDK.h"
        }
      break;  
      
      case '3':
        if(longDK1.isThreeColor_Idle())
        {
          longDK1.startThreeColor();  //gui yeu cau den "longDK.h"
        }
      break; 
    
      case '4':
        longDK1.urgent4();
      break;  

      case '5':
        longDK1.urgent5();
      break;

      case '6':0
        longDK1.startThreeColor1();
      break;
    }
  }
}
  

