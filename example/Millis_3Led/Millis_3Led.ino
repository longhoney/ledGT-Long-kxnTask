/*
  Blink without Delay

  Turns on and off a light emitting diode (LED) connected to a digital pin,
  without using the delay() function. This means that other code can run at the
  same time without being interrupted by the LED code.

  This example code is in the public domain.
  https://docs.arduino.cc/built-in-examples/digital/BlinkWithoutDelay/

  The circuit:
  - Use the traffic light module
  - Wiring: G1 = D3, Y1 = D4, R1 = D5, GND
*/

// constants won't change. Used here to set a pin number:
const int G1 = 3;  // the number of the LED pin
const int Y1 = 4;  // the number of the LED pin
const int R1 = 5;  // the number of the LED pin

// Variables will change:
int G1State = LOW;  // ledState used to set the LED
int Y1State = LOW;  // ledState used to set the LED
int R1State = HIGH;  // ledState used to set the LED

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;  // will store last time LED was updated

// constants won't change:
//const long interval = 1000;  // interval at which to blink (milliseconds)
const long R1time = 3000;
const long G1time = 2000 + R1time;
const long Y1time = 1000 + G1time;

void setup() {
  // set the digital pin as output:
  pinMode(G1, OUTPUT);
  pinMode(Y1, OUTPUT);
  pinMode(R1, OUTPUT);
  digitalWrite(G1, G1State);
  digitalWrite(Y1, Y1State);
  digitalWrite(R1, R1State);
}

void loop() {
  // here is where you'd put code that needs to be running all the time.

  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= R1time) {
    digitalWrite(R1, LOW);
    digitalWrite(G1, HIGH);
  }

  if (currentMillis - previousMillis >= G1time) {
    digitalWrite(G1, LOW);
    digitalWrite(Y1, HIGH);
  } 
  if (currentMillis - previousMillis >= Y1time) {
    previousMillis = currentMillis;
    digitalWrite(Y1, LOW);
    digitalWrite(R1, HIGH);
  }
}
