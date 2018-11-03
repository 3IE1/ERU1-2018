/*
 Code for two devices: 
 1) A thermistor records temperatures. If temperature drops below 15degC, a rendition of Jingle Bells is played on a buzzer. 
 2) A photoreceptor records light. When the lights in a room are turned off, a red and a green LED light simultaneously turn on 
 (and turn back off again if room lights are turned on)

 Code written by Felipe Rivera-Madrinan, Theresia Sakhi, and Ruby Yee; some portions adapted from Arduino examples
 */
 
#include <math.h>
#include "pitch.h" //include pitch library

const int analogInPin = A1;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 4; // Analog output pin that the LED is attached to


int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)


double Thermistor(int RawADC) {
 // Inputs ADC Value from Thermistor and outputs Temperature in Celsius
 //  requires: include <math.h>
 // Utilizes the Steinhart-Hart Thermistor Equation:
 //    Temperature in Kelvin = 1 / {A + B[ln(R)] + C[ln(R)]^3}
 //    where A = 0.001129148, B = 0.000234125 and C = 8.76741E-08
 long Resistance;  double Temp;  // Dual-Purpose variable to save space.

 Resistance=10000.0*((1024.0/RawADC) - 1);  // Assuming a 10k Thermistor.  Calculation is actually: Resistance = (1024 /ADC -1) * BalanceResistor
// For a GND-Thermistor-PullUp--Varef circuit it would be Rtherm=Rpullup/(1024.0/ADC-1)
 Temp = log(Resistance); // Saving the Log(resistance) so not to calculate it 4 times later. // "Temp" means "Temporary" on this line.
 Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));   // Now it means both "Temporary" and "Temperature"
 Temp = Temp - 273.15;  // Convert Kelvin to Celsius                                         // Now it only means "Temperature"

 // BEGIN- Remove these lines for the function not to display anything
  Serial.print("ADC: "); Serial.print(RawADC); Serial.print("/1024");  // Print out RAW ADC Number
  Serial.print(", Volts: "); printDouble(((RawADC*4.860)/1024.0),3);   // 4.860 volts is what my USB Port outputs.
  Serial.print(", Resistance: "); Serial.print(Resistance); Serial.print("ohms");
 // END- Remove these lines for the function not to display anything

 return Temp;  // Return the Temperature
}

void printDouble(double val, byte precision) {
  // prints val with number of decimal places determine by precision
  // precision is a number from 0 to 6 indicating the desired decimal places
  // example: printDouble(3.1415, 2); // prints 3.14 (two decimal places)
  Serial.print (int(val));  //prints the int part
  if( precision > 0) {
    Serial.print("."); // print the decimal point
    unsigned long frac, mult = 1;
    byte padding = precision -1;
    while(precision--) mult *=10;
    if(val >= 0) frac = (val - int(val)) * mult; else frac = (int(val) - val) * mult;
    unsigned long frac1 = frac;
    while(frac1 /= 10) padding--;
    while(padding--) Serial.print("0");
    Serial.print(frac,DEC) ; //this section is creating the output in the serial monitor
  }
}

void setup() {
 Serial.begin(115200);
 Serial.begin(9600); //defines frequencies
   pinMode(analogOutPin, OUTPUT); //instructions for analog pin
}

#define ThermistorPIN 0   // Using Analog Pin 0
double temp; //defines temperature variable
void loop() {

 temp=Thermistor(analogRead(ThermistorPIN));           // read ADC and convert it to Celsius
 Serial.print(", Celsius: "); printDouble(temp,3);     // display Celsius
 while (temp < 15){
// notes in the melody:
int melody[] = {
  NOTE_E4, NOTE_E4, NOTE_E4,NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_G4, NOTE_C4, NOTE_D4, NOTE_E4,
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 4, 2, 4, 4, 2, 4, 4, 3, 8, 1
};
for (int thisNote = 0; thisNote < 11; thisNote++) {

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
  break;
 }

 Serial.println("");                                   // End of Line
 delay(100);                                           // Delay a bit to not Serial.print faster than the serial connection can output

 // read the analog in value:
  sensorValue = analogRead(analogInPin);

  if (sensorValue > 400) {
  digitalWrite(analogOutPin, LOW);   
  }
  else {
  digitalWrite(analogOutPin, HIGH);  
  }
 /* Map it to the range of the analog out:
  outputValue = map(sensorValue, 220, 700, 0, 255);
  Change the analog out value:
  analogWrite(analogOutPin, outputValue);*/

  // print the results to the Serial Monitor:
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.println(outputValue);

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(2);
 }
// note durations: 4 = quarter note, 8 = eighth note, etc.:
//int noteDurations[] = {
 // 0
 // };

 
