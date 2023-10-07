#include <Arduino.h>
#include <Wire.h>
#include "K30_FR_For_Drone.h"

K30_FR_For_Drone::K30_FR_For_Drone(int _address) {
  Wire.begin();  //I2Cの開始
  address = _adress;
}

int byte K30_FR_For_Drone::errorCheck(int &eroorCode) {
  retryCount = 0;
  while (retryCount <= 2) {
    byte recValue[4] = { 0, 0, 0, 0 };
    //エラーコードの入ってるメモリ(0x001E)にアクセスを指定
    Wire.beginTransmission(address);
    Wire.write(0x22);  //Read RAM head(send 2 byte)
    Wire.write(0x00);  //RAM address head
    Wire.write(0x1E);  //RAM address end
    Wire.write(0x40);  //check sum
    Wire.endTransmission();
    delay(30);

    //CO2濃度の受信
    Wire.requestFrom(address, 3);
    delay(20);
    //checkSum
    byte i = 0;
    while (Wire.available()) {
      recValue[i] = Wire.read();
      i++;
    }

    byte checkSum = recValue[0] + recValue[1];
    errorCode = recValue[1];  //エラーコードの代入

    if (i == 0) {  //返答無し
      return 2;
    } else if (checkSum == recValue[2]) {  //checksumが合っていた場合
      return 0;
    } else {  //checkSumが合わない場合
      retryCount++;
    }
    delay(100);
  }
  return 1;  //checkSumが何度も合わない場合
}
bool K30_FR_For_Drone::ABCSetup(int hour) {
  retryCount = 0;
  while (retryCount <= 2) {
    byte recValue[4] = { 0, 0, 0, 0 };
    //エラーコードの入ってるメモリ(0x001E)にアクセスを指定
    Wire.beginTransmission(address);
    Wire.write(0x22);  //Read RAM head(send 2 byte)
    Wire.write(0x00);  //RAM address head
    Wire.write(0x1E);  //RAM address end
    Wire.write(0x40);  //check sum
    Wire.endTransmission();
    delay(30);

    //CO2濃度の受信
    Wire.requestFrom(address, 3);
    delay(20);
    //checkSum
    byte i = 0;
    while (Wire.available()) {
      recValue[i] = Wire.read();
      i++;
    }

    byte checkSum = recValue[0] + recValue[1];
    errorCode = recValue[1];  //エラーコードの代入

    if (i == 0) {  //返答無し
      return 2;
    } else if (checkSum == recValue[2]) {  //checksumが合っていた場合
      return 0;
    } else {  //checkSumが合わない場合
      retryCount++;
    }
    delay(100);
  }
  return 1;  //checkSumが何度も合わない場合
}
int K30_FR_For_Drone::read(int &CO2level) {
  retryCount = 0;
  while (retryCount <= 2) {
    byte recValue[4] = { 0, 0, 0, 0 };
    //CO2濃度の入ってるメモリ(0x0008)にアクセスを指定
    Wire.beginTransmission(address);
    Wire.write(0x22);  //Read RAM head(send 2 byte)
    Wire.write(0x00);  //RAM address head
    Wire.write(0x08);  //RAM address end
    Wire.write(0x2A);  //check sum
    Wire.endTransmission();
    delay(30);

    //CO2濃度の受信
    Wire.requestFrom(address, 4);
    delay(20);
    //checkSum
    byte i = 0;
    while (Wire.available()) {
      recValue[i] = Wire.read();
      i++;
    }

    byte checkSum = recValue[0] + recValue[1] + recValue[2];
    CO2level = (recValue[1] << 8) + recValue[2];  //CO2濃度の代入

    if (i == 0) {  //返答無し
      return 2;
    } else if (checkSum == recValue[3]) {  //checksumが合っていた場合
      return 0;
    } else {  //checkSumが合わない場合
      retryCount++;
    }
    delay(100);
  }
  return 1;  //checkSumが何度も合わない場合
}