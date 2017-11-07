// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

// Which pins on the Arduino are connected to the levers?
#define SW1            2
#define SW2            3
#define SW3            4
#define SW4            5

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN            8

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      4                                                           

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second

void setup() {
  Serial.begin(9600); // Initialize serial communication for debug
  
  pixels.begin(); // This initializes the NeoPixel library.'
  delay(1);       // This pauses
  
  // initialize all the neopixels as on, green
    for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(25,0,0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    } 
}

void loop() {
  int lever1 = digitalRead(SW1);
  if (lever1 == 0) {
      pixels.setPixelColor(0, pixels.Color(0,25,0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
  }
}
