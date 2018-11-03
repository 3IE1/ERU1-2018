/* Code for turning on and sweeping a Servo motor and three LEDs using a toggle switch.
   Written by Felipe Rivera-Madrinan, Theresia Sakhi, Ruby Yee 
   Adapted portions of code from Arduino examples ("Servo > Sweep")*/

#include <Servo.h> //includes Servo library
int ledpin = 13;
int switchpin = 7;
int switchval = 0; //defining variables and pin numbers

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(13,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  switchval = digitalRead(switchpin); // setting up toggle switch (establishing what to do when in "1" or "0" position)
  Serial.println(switchval);
  if(switchval==1){
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    digitalWrite(ledpin,HIGH);
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    digitalWrite(ledpin,HIGH);
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
}
