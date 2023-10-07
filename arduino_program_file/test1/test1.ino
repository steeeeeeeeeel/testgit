#include <Wire.h>
void setup() {
  Serial.begin(9600);
  Wire.begin();
}

int address = 0x68;
int CO2level;
void loop() {
  
  byte recValue[4] = {0,0,0,0};

  Serial.print("read K30 = ");

  Wire.beginTransmission(address);
  Wire.write(0x22);
  Wire.write(0x00);
  Wire.write(0x08);
  Wire.write(0x2A);
  Wire.endTransmission();
  delay(30); 

  Wire.requestFrom(address,4);
  delay(20);

  byte i=0;
  while(Wire.available())
  {
    recValue[i] = Wire.read();
    i++;
  }

  byte checkSum = recValue[0] + recValue[1] + recValue[2];
  CO2level = (recValue[1] << 8) + recValue[2];
  if (i == 0){
    Serial.println("doesn't responce");
  }
  else if(checkSum == recValue[3]){
    Serial.println(CO2level);
  }
  else{
    Serial.println("error responce");
  }
  delay(2000);
}
