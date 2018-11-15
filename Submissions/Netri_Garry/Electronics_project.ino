
 /*
 * Sensitive temperature detecting appliance.
 * Turns RGB LED Red if temperature is greater than 25 degrees Celsius. 
 * Turns RGB LED Blue if temperature is less than 25 degrees Celsius. 
 * A total of two temperature ranges correspond to two distinct notes played through the buzzer. 
 * The buzzer can be turned on and off with the button; the RGB LED runs independent of the button function. 
 * Created Nov 3, 2018
 * Garry Vinayak and Netri Pajankar 
 */

#include <math.h>

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

  // BEGIN- Remove these lines for the function not to display anything
  //Serial.print("ADC: "); 
  //Serial.print(RawADC); 
  //Serial.print("/1024");                           // Print out RAW ADC Number
  //Serial.print(", vcc: ");
  //Serial.print(vcc,2);
  //Serial.print(", pad: ");
  //Serial.print(pad/1000,3);
  //Serial.print(" Kohms, Volts: "); 
  //Serial.print(((RawADC*vcc)/1024.0),3);   
  //Serial.print(", Resistance: "); 
  //Serial.print(Resistance);
  //Serial.print(" ohms, ");
  // END- Remove these lines for the function not to display anything

  // Uncomment this line for the function to return Fahrenheit instead.
  //temp = (Temp * 9.0)/ 5.0 + 32.0;                  // Convert to Fahrenheit
  return Temp;                                      // Return the Temperature

  
//Converts note duration from notes to milliseconds 
}
float noteDur(int nd){    
 int noteDuration2 = 1000 / nd;
return noteDuration2;
}

//Indicates pin input from the arduino to the RGB LED
int redPin = 11;
int greenPin = 10;
int bluePin = 9;
int Soundflag = 1; //Indicates if button is pressed down, i.e, circuit is complete and current is flowing
float temp;
int buttonState = 0;
const int buttonPin = 2; 
//uncomment this line if using a Common Anode LED
//#define COMMON_ANODE //  Defines the function of the LED and the max current flow possible (255)
void setColor(int red, int green, int blue)//Amount of current flowing for specific colour 
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}

#include "pitches.h"//  Identifies all the notes the corresponding current flow
// notes in the melody:
int melody[] = {
  NOTE_B0, NOTE_D5
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  1, 1
};



void setup() {
  Serial.begin(115200);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT); 

/*
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }  
*/
}



void loop() {

  temp=Thermistor(analogRead(ThermistorPIN));       // read ADC and  convert it to Celsius
  Serial.print("Celsius: "); 
  Serial.print(temp,1);                             // display Celsius
  //temp = (temp * 9.0)/ 5.0 + 32.0;                  // converts to  Fahrenheit
  //Serial.print(", Fahrenheit: "); 
  //Serial.print(temp,1);                             // display  Fahrenheit
  Serial.println("");                                   
  delay(500);                                      // Delay a bit... 
  
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
Serial.print("buttonState = ");
Serial.println(buttonState); 
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) //1-1=0; 0 indicates button is not pressed, 1 inidicates button is pressed
  {
    Soundflag = abs(1-Soundflag);
  } 
 if (temp >= 25) {
  setColor(255, 0, 0);  // red
  if (Soundflag == 1) {
  tone(8, melody[1], noteDur(1));}
 }
 else if (temp < 25) {
  setColor(0, 0, 255);  // blue
    if (Soundflag == 1) {
  tone(8, melody[0], noteDur(1));}
 }
}
