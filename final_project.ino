int lightLedPin = 4;
int breathLedPin = 7;
int waterLedPin = 8;
int buttonPin = 3;

void setup() {
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
  //output
  pinMode(lightLedPin, OUTPUT);
  pinMode(breathLedPin, OUTPUT);
  pinMode(waterLedPin, OUTPUT);
  //input_pllup resistor
  pinMode(2, INPUT_PULLUP);
  pinMode(buttonPin, INPUT_PULLUP);
  
  while (Serial.available() <= 0) {
    digitalWrite(LED_BUILTIN, HIGH); //on/blink while waiting for serial data
    Serial.println("512,1023,1,1");  //starting message
    delay(300);            
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
  }
}

void loop() {
  while (Serial.available()) {
    digitalWrite(LED_BUILTIN, HIGH); 

    int lightState = Serial.parseInt();
    int breathState = Serial.parseInt();
    int waterState = Serial.parseInt();

    if (Serial.read() == '\n') {
      digitalWrite(lightLedPin, lightState);
      digitalWrite(breathLedPin, breathState);
      digitalWrite(waterLedPin, waterState);

      //send to p5
      int breathing = analogRead(A0);
      delay(5); 
      int light = analogRead(A1);
      delay(5);
      int sipping = digitalRead(2);
      int buttonState = digitalRead(buttonPin);
        
      Serial.print(breathing);
      Serial.print(',');
      Serial.print(light);
      Serial.print(',');
      Serial.print(sipping);
      Serial.print(',');             
      Serial.println(buttonState);
    }
  }
  digitalWrite(LED_BUILTIN, LOW);
}
