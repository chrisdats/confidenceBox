/* confidenceBox.ino
 Christopher Datsikas
 Assignment 7 DPI - Nov 6 2017
 */

// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#include <avr/power.h>
#include <Servo.h>


// Which pins on the Arduino are connected to the levers?
int leverPins[] = {
  2,3,4,5};
// How many levers are connected?
int leverCount = 4; 

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN            6
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      4                                                           

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position
#define OPEN          90
#define CLOSE          0


void setup() {
  Serial.begin(9600); // Initialize serial communication for debug

  pixels.begin(); // This initializes the NeoPixel library.'

  // initialize all the neopixels as on, red
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(25,0,0)); // Moderately bright red color.
    pixels.show(); // This sends the updated pixel color to the hardware.
  } 

  // initialize all the pins connected to the lever switches as INPUT with Internal Pull-Up
  for (int thisPin = 0; thisPin < leverCount; thisPin++) {  
    pinMode(leverPins[thisPin], INPUT);
    digitalWrite(leverPins[thisPin], HIGH);
  }
  
  // initialize the servo
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(OPEN);
  Serial.println("Servo attached and set to 90");
  
  // lock the box
  for (pos = OPEN; pos >= 1; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    Serial.println(pos);
    delay(10);                       // waits 15ms for the servo to reach the position
  }
  myservo.detach();  // attaches the servo on pin 9 to the servo object
  delay(3000);
  Serial.println("Setup Complete");
}

void loop() {

  for (int thisPin = 0; thisPin < leverCount; thisPin++) {    // iterate through all the levers
    int leverState = digitalRead(leverPins[thisPin]);         // store value of lever state
    if (leverState == 0) {                                    // if lever is pulled down, turn green
      pixels.setPixelColor(thisPin, pixels.Color(0,25,0)); // Moderately bright green color.
      pixels.show();                                       // Update pixel color.
    }
    else if (leverState == 1) {                              // if lever is pulled up (or in original position), stay/turn red
      pixels.setPixelColor(thisPin, pixels.Color(25,0,0)); // Moderately bright red color.
      pixels.show();                                       // Update pixel color.
    }
  }
}



