#define fanPulse 4
#define fanControl 9
unsigned long lastPulseTime = 0;
unsigned int pulseInterval;
unsigned long cur;
int rpm ;
ISR(PCINT2_vect) {
  if(digitalRead(fanPulse) == HIGH){
  cur = micros();
  if((cur - lastPulseTime) <= 8108){//ノイズ対策(ソフト上)
    return;
  } 
  pulseInterval = cur - lastPulseTime; // 前回のエッジとの差分
  lastPulseTime = cur;
  }
}

/*void senseRotation(){
  cur = micros();
  pulseInterval = cur - lastPulseTime; // 前回のエッジとの差分
  lastPulseTime = cur;
}
*/
void setup() {
  //attachInterrupt(0, senseRotation, FALLING); 
  PCICR |= B00000100;
  PCMSK2 |= B00010000;
  Serial.begin(9600);
  //pinMode(fanPulse,INPUT);
  //pinMode(fanControl,OUTPUT);
  analogWrite(fanControl,120);
}

void loop() {
  //digitalWrite(fanControl,HIGH);
  rpm = 60000000/(pulseInterval*2);
  Serial.println(rpm);
  delay(1000);
}
