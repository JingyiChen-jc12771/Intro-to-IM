//include the pitches file
#include "pitches.h"
//declare pins
int buzzerPin=8;
int analogPin=A0;
int distPin=9;
int echoPin=10;
int switchPin=11;
//create an array of notes to remove the bad sounds and improve the beat
int scale[]={NOTE_C4, NOTE_D4, NOTE_E4, NOTE_G4, NOTE_A4, 
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_G5, NOTE_A5};
int numNotes =10;
//unsigned long is for very long numbers, used because startMilis might exceed 32,776.
unsigned long startMillis=0;
int beatStep =0;

void setup() {
  // put your setup code here, to run once:
  //set pin modes
pinMode(buzzerPin,OUTPUT);
pinMode(distPin,OUTPUT);
pinMode(echoPin,INPUT);
//Use the resistor in the arduino board
pinMode(switchPin, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  //long is used for both duration and cm because they nmay exceed the int limit
long duration,cm;
int switchState = digitalRead(switchPin);
//measuring chunk for the ultrasonic distance sensor
digitalWrite(distPin,LOW);
delayMicroseconds(2);
digitalWrite(distPin, HIGH);
delayMicroseconds(10);
digitalWrite(distPin, LOW);
//records the time between output of ultrasound and echo. 10000 sets a limit in case there is not close enought object, it prevents the program from stopping completely by setting cm to 0.
duration=pulseIn(echoPin,HIGH,10000);
//uses the convertion function to convert the time to distance
cm = microsecondsToCentimeters(duration);
//if the distance of object is further than 50cm away treat it as 50cm, this limits the range of distance.
if(cm==0||cm>50){cm=50;}
//map the distance to the array of notes, 2 is the reliable begining measurement of the sensor
int noteIndex = map(cm, 2, 50, 0, numNotes - 1);
int currentNote=scale[noteIndex];
int analogValue=analogRead(analogPin);
//changes the time between beats, 150 and 800 are reasonable interval limits to keep it sounding nice
int tempo = map(analogValue,0,1023,150,800);

unsigned long currentMillis=millis();
//if time after last beet is larger than time between beats, update timer and play new beat.
if (currentMillis - startMillis >= tempo) {
    startMillis = currentMillis; 
    beatStep++;
    //the beat generation
    //switch controls two states, one where the beats play at a steady tone
    if(switchState==HIGH){
      tone(buzzerPin,currentNote,50);
      //In the other state the beat is deeper at even beats and lighter at odd beats
    }else{if(beatStep%2==0){
      tone(buzzerPin,100,50);
    }else{
      tone(buzzerPin,currentNote,50);
    }
  }
}
}
//the function to convert time to distance, 10000 time would result in 0cm
long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}