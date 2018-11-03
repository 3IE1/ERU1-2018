/* This program sounds an alarm, flashes the RGB LED red, and spins the roatitonal motor when the thermister reads a temperature over 24 degrees or under 20 degrees C. 
This code was primarily taken from Arduino examples and modified for our project. 
By Matty and Sarah */

 //assigns inputs to their appropriate ports
#define TEMP_PIN A0
#define RED_PIN 9
#define GREEN_PIN 10
#define BLUE_PIN 11
#define speakerPin 8
#define LoveMyFans 6

//outlines the pitch of the notes played by speaker 
#include "pitches.h"
int melody[] = {
  NOTE_C4, NOTE_G3
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8
};

int adc = 0;
int blue = 0, red = 0;
double temp = 0;
double ReadThermistor(int adc) {

  double resistance = ((1024.0/adc) - 1);    //calculate from voltage divider, for 10k resistor
  double Temp = log(resistance);

  // calculate the temperature, in K, using 4 thermistor model/material specific parameters A, B, C, D
  // here we use the values for the Sparkfun/Hactronics version of the Vishay 10k NTC thermistor
  Temp = 1 / (0.003354016 + 0.0002569850 * Temp + 0.000002620131 * Temp * Temp + 0.00000006383091 * Temp * Temp * Temp);
  Temp = Temp - 273.15;            // Convert Kelvin to Celsius
  return Temp;
}

//diffirentiates the red and blue lights 
void setLED(int blue, int red){
  analogWrite(BLUE_PIN, blue);
  analogWrite(RED_PIN, red);
}

//this library allows motor rotation
#include <Servo.h>
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
int pos = 0;    // variable to store the servo position

//defines the inputs and outputs from our machine to the environment 
void setup(){
  Serial.begin(9600);
  pinMode(BLUE_PIN, OUTPUT); 
  pinMode(RED_PIN, OUTPUT); 
  pinMode(GREEN_PIN, OUTPUT);  
  pinMode(TEMP_PIN, INPUT);
  pinMode(4,OUTPUT);
  pinMode(speakerPin, OUTPUT);
  myservo.attach(6);

}

//the main loop that ensures the alarm will blink, sound, and the motor will spin
void loop(){
adc = analogRead(TEMP_PIN);
  temp = ReadThermistor(adc);
  Serial.print(temp);
    red = map(temp, 21, 30, 0, 255);
  blue = 255 - red;
  
  Serial.print("red = ");Serial.print(red);
  Serial.print("blue = ");Serial.println(blue);
  setLED(blue, red);

 //defines the tmeperature range at which the alarm does not play   
   if (temp > 24 || temp < 20) {
    
    //audio alarm 
  for (int thisNote = 0; thisNote < 2; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(speakerPin, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(speakerPin);        
}

//turns the motor on when HIGH and off when LOW at temperature previously set
  digitalWrite(4,HIGH);
  setLED(0, 255);
delay(500);
   } 
else {
    digitalWrite(4,LOW);

}
}
