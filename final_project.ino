// Inputs:
// - A0 - sensor connected as voltage divider (breathing)
// - A1 - sensor connected as voltage divider (light)
// - 2  - switch/button (sipping)
// - 3  - switch/button (main button)
//
// Outputs:
// - 4 - LED (light state)
// - 7 - LED (breath state)
// - 8 - LED (water state)

int lightLedPin = 4;
int breathLedPin = 7;
int waterLedPin = 8;
int buttonPin = 3;

void setup() {
  // Start serial communication so we can send data
  // over the USB connection to our p5js sketch
  Serial.begin(9600);
  
  // We'll use the builtin LED as a status output.
  pinMode(LED_BUILTIN, OUTPUT);

  // Outputs on these pins
  pinMode(lightLedPin, OUTPUT);
  pinMode(breathLedPin, OUTPUT);
  pinMode(waterLedPin, OUTPUT);

  // Inputs on these pins
  pinMode(2, INPUT_PULLUP);
  pinMode(buttonPin, INPUT_PULLUP);
  
  // start the handshake
  while (Serial.available() <= 0) {
    digitalWrite(LED_BUILTIN, HIGH); // on/blink while waiting for serial data
    Serial.println("512,1023,1,1");  // send a starting message
    delay(300);            // wait 1/3 second
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
  }
}

void loop() {
  // wait for data from p5 before doing something
  while (Serial.available()) {
    digitalWrite(LED_BUILTIN, HIGH); // led on while receiving data

    // Use parseInt() to grab the numbers, just like the classroom example
    int lightState = Serial.parseInt();
    int breathState = Serial.parseInt();
    int waterState = Serial.parseInt();

    // Check if we reached the end of the line
    if (Serial.read() == '\n') {
      digitalWrite(lightLedPin, lightState);
      digitalWrite(breathLedPin, breathState);
      digitalWrite(waterLedPin, waterState);

      // SEND TO P5
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
