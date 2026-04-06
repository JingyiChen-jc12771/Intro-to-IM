int analogPin=A2;
int digitalPin=2;
int analogLed=11;
int digitalLed=13;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(analogLed, OUTPUT);
pinMode(digitalLed, OUTPUT);
pinMode(digitalPin, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
int sensorValue=analogRead(analogPin);
int buttonState=digitalRead(digitalPin);
Serial.println(sensorValue);
if (buttonState==LOW){
  //turn off yellow LED
  analogWrite(analogLed,0);
  //Bling red LED
  digitalWrite(digitalLed,HIGH);
  delay(sensorValue);        
  digitalWrite(digitalLed, LOW);          
  delay(sensorValue);
}else{
  //Turn off red LED
  digitalWrite(digitalLed,LOW);
  //Fade yellow LED
  analogWrite(analogLed, sensorValue/4);
  delay(30);
}
}
