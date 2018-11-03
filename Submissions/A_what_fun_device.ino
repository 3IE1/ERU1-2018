
/*
 This code was made by Gillian and Pat. We created a device that will convert temperature data from the thermistor to a RGB LED light.
This light will be bluer at colder temperatures and redder at warmer temperatures. At 30 degress Celsius, a cool little tune will play. 
Also, two buttons were connected to different speakers to play two pitches. What fun. 

Some code was copied from Arduino tutorials on using a thermistor (link: http://playground.arduino.cc/ComponentLib/Thermistor2) and some code was copied
from adafruit's 'Arduino Lesson 3. RGB LEDs' (link: https://learn.adafruit.com/adafruit-arduino-lesson-3-rgb-leds/arduino-sketch). 
 
 */


#define ThermistorPIN 0                 // Analog Pin 0

float vcc = 4.91;                       // only used for display purposes, if used
                                        // set to the measured Vcc.
float pad = 9850;                       // balance/pad resistor value, set this to
                                        // the measured resistance of your pad resistor
float thermr = 10000;                   // thermistor nominal resistance

float Thermistor(int RawADC) {
  long Resistance;  
  float Temp;  // Dual-Purpose variable to save space.

  Resistance=pad*((1024.0 / RawADC) - 1); 
  Temp = log(Resistance); // Saving the Log(resistance) so not to calculate  it 4 times later
  Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));
  Temp = Temp - 273.15;  // Convert Kelvin to Celsius                      

  // Uncomment this line for the function to return Fahrenheit instead.
  //temp = (Temp * 9.0)/ 5.0 + 32.0;                  // Convert to Fahrenheit
  return Temp;                                      // Return the Temperature
}

#include "pitches.h"


const int button1Pin = 7;     // the number of the pushbutton 1 pin
const int button2Pin = 8;     // the number of the pushbutton 2 pin
const int buzzerC6Pin = 12;      // the number of the first buzzer
const int buzzerG6Pin = 4;      // the number of the second buzzer

// variables will change:
int button1State = 0;         // variable for reading the pushbutton 1 status
int button2State = 0;         // variable for reading the pushbutton 2 status

// notes played by the button buzzers:
int noteC6 = {
  NOTE_C3
};
int noteG6 = {
  NOTE_G5
};

//defining LED pin as variables:
int redPin = 11;   
int greenPin = 10;
int bluePin = 9;

//defining temperature-related buzzer as a variable:
int buzzerPin = 2;

//defining base setting for red and blue
int red = 0;
int blue =0;

//the pitches that will play when temp is <= 15 or >= 30
int melody[] = {
  NOTE_C5,NOTE_G5,NOTE_C5,NOTE_G5,NOTE_C5,NOTE_G5,NOTE_C5,NOTE_G5
};

// note durations (of pitches above): 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 4, 4, 4,4, 4,4, 4 
};

void setup() {
  Serial.begin(115200);
  
  // initialize the LED pins as outputs:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT); 
  // initialize the buzzer pins as outputs:
  pinMode(buzzerC6Pin, OUTPUT);
  pinMode(buzzerG6Pin, OUTPUT);
  // initialize the pushbutton pins as inputs:
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  //Serial.begin(9600);
}

void loop() {
  float temp;
  temp=Thermistor(analogRead(ThermistorPIN));       // read ADC and  convert it to Celsius
  Serial.print("Celsius: "); 
  Serial.print(temp,1);                             // display Celsius
  //temp = (temp * 9.0)/ 5.0 + 32.0;                  // converts to  Fahrenheit
  //Serial.print(", Fahrenheit: "); 
  //Serial.print(temp,1);                             // display  Fahrenheit
  Serial.println("");                                   
  delay(500);                                      // Delay a bit... 

red = map(temp, 20, 35, 0, 255); //mapping temperature range to intensity of red light
blue = map(temp, 15, 29, 255, 0); //mapping temperature range to intensity of blue light

// if then statement occuring when temperature is equal or greater than 30, that makes the blue light turn off, 
// the red light full intensity, and the buzzer play a fast melody:
if (temp >= 30){
  blue = 0;
  red = 255;
    for (int thisNote = 0; thisNote < 8; thisNote++) {
    int noteDuration = 500 / noteDurations[thisNote];
    tone(buzzerPin, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 0.4;
    delay(pauseBetweenNotes);
  }
}
else if (temp <= 20){       // when temp is below 20, the red light turns off
  red = 0;
} 
else if (temp <= 20){       // when temp is below 15, the blue light becomes full intenity and the buzzer plays a slow melody
  blue = 255;
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    int noteDuration = 2000 / noteDurations[thisNote];
    tone(buzzerPin, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    }
}

//Reading the button states so that the arduino recognize when the buttons are pressed:
 button1State = digitalRead(button1Pin);
 button2State = digitalRead(button2Pin);

  //printing the read button states for debugging purposes:
  //Serial.print("button 1: ");Serial.print(button1State);
  //Serial.print("  button 2: ");Serial.print(button2State); 
  //Serial.println("");

  //if then statement saying that if button 1 is pressed, note C will play:
  if (button1State == HIGH){
    tone(buzzerC6Pin, noteC6);
  }
  else {
    noTone(buzzerC6Pin);
  };

  //if then statement saying that if button 2 is pressed, note G will play:
  if (button2State == HIGH){
    tone(buzzerG6Pin, noteG6);
  } 
  else {
    noTone(buzzerG6Pin);
  }

//activating the setColor function so that the LED displays the colors (previously mapped by the temperature):
setColor(red, 0, blue);

}


// Creating the setColor function that includes values for red, green and blue in the LED:
 void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  //Writing pin values to output colour values:
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}
