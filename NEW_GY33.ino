/////////////////////
/*
  GY33----MINI
  VCC----VCC
  GND----GND
  1:RX---TX,send A5 01 A6 to GY-33
  2:TX---RX
  3:MINI_TX---FT232_RX
*/
//////////////////
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10,11); // RX, TX

unsigned char Re_buf[11], counter = 0;
unsigned char sign = 0;
byte rgb[3] = {0};
void setup() {
  Serial.begin(9600);
 // Serial.print("hello");
  mySerial.begin(115200);
  delay(1);
  mySerial.write(0XA5);
  mySerial.write(0X01);    //初始化,连续输出模式
  mySerial.write(0XA6);    //初始化,连续输出模式
}

void loop() {
  unsigned char i = 0, sum = 0;
  if (sign == 1)
  {
    Serial.println("h");
    sign = 0;
    for (i = 0; i < 7; i++)
      sum += Re_buf[i];
    if (sum == Re_buf[i] )     //检查帧头，帧尾
    {
      rgb[0] = Re_buf[4];
      rgb[1] = Re_buf[5];
      rgb[2] = Re_buf[6];
      Serial.print("r:");
      Serial.print( rgb[0], DEC);
      Serial.print(",g:");
      Serial.print( rgb[1], DEC);
      Serial.print(",b:");
      Serial.println( rgb[2], DEC);
    }
  }
  //Serial.println("e");
  while (mySerial.available()) {
      Serial.print("hello");
    byte  readedchar = mySerial.read();
    //Serial.write(readedchar);
    Re_buf[counter] = (unsigned char)readedchar;
    if (counter == 0 && Re_buf[0] != 0x5A) return; // 检查帧头
    counter++;
    if (counter == 8)             //接收到数据
    {
      counter = 0;               //重新赋值，准备下一帧数据的接收
      sign = 1;
    }
  }
}

