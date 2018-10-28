/*
<name of your function>

<description of what your function does>
<provide details of the wiring for your circuit, or upload a fritzing diagram with this sketch>



created <date> by <name(s)>
modified <date> by <name(s)>
<summary of any major modifications (if applicable)>

*/

//<Use line or block comments to describe what is being done in a block of code>
int var1 = 2; // <explanation of the variable>
float var2 = pi();

//<Use line or block comments to describe what is being done in this section
void setup() {                
  // <example:> initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
}

//<Use line or block comments to describe what is being done in this section
void loop() {
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second
}
