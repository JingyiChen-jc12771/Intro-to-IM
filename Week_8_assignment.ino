void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  pinMode(A2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 int buttonState = digitalRead(A2);

  if (buttonState == HIGH) {
    //Not repeating the code uses the void loop and makes the LED blink as long as the circuit is connected.
    digitalWrite(13, HIGH);
    delay(200);             
    digitalWrite(13, LOW);
    delay(200); 
  } else  {
    digitalWrite(13, LOW);    
  }
}
