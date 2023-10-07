#define TX 2
#define RX 3
#define fan1Pulse
#define fan2Pulse
#define fan1Pin1
#define fan1Pin2
#define fan2Pin1
#define fan2Pin2
#define Fan1Pwm
#define Fan2Pwm
#include <SoftwareSerial.h>
SoftwareSerial mySerial(RX,TX);
void Fan1Speed();
void Fan2Speed();

void setup() {
  mySerial.begin(9600); 
  attachInterrupt(1)
  

}

void loop() {
  

}
