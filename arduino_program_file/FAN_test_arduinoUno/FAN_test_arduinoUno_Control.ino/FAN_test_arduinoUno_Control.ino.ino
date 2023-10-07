void setup() {
  pinMode(9,OUTPUT);
  // put your setup code here, to run once:

}

void loop() {
  analogWrite(9,255);
  delay(1000);
  analogWrite(9,122);
  delay(1000);
  analogWrite(9,1);
  delay(1000);
  // put your main code here, to run repeatedly:

}
