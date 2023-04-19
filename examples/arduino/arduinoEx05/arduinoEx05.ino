// Progressive examples, toward PyGame Zero Xi (Extended Interaction) integration
// Brygg Ullmer, Clemson University
// Support by NSF CNS-1828611
// Begun 2023-04

#define LED0 13
#include "enoLedmapper.h"

#define NUMPIXELS 1
Adafruit_NeoPixel pixels(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

////////////////// setup /////////////////////

void setup() {
  pinMode(13, OUTPUT); // initialize digital pin 13 as an output.
  
  #if defined(NEOPIXEL_POWER)
  pinMode(NEOPIXEL_POWER, OUTPUT);
  digitalWrite(NEOPIXEL_POWER, HIGH);
  #endif

  Serial.begin(9600);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.setBrightness(7); // not so bright
}

////////////////// loop/////////////////////

void loop() {
}

///end///
