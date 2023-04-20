// Enodia LED mapper
// Brygg Ullmer, Clemson University
// Partial support from NSF CNS-1828611
// Begun 2023-04
// LLGPL3

//#include <Adafruit_NeoPixel.h>
#include "enoLightmapper.h"
#include "enoLedmapper.h"

///////////////////////////// constructor /////////////////////////////

enoLedmapper::enoLedmapper(int numLights, enoColormapper *ecm, int whichChain, int maxBrightVal) : 
  enoLightmapper(numLights, ecm, whichChain, maxBrightVal) {
  initLeds();
}

///////////////////////////// initiate leds /////////////////////////////
  
void enoLedmapper::initLeds() {

  #if defined(NEOPIXEL_POWER)
  // If this board has a power control pin, we must set it to output and high
  // in order to enable the NeoPixels. We put this in an #if defined so it can
  // be reused for other boards without compilation errors
  pinMode(NEOPIXEL_POWER, OUTPUT);
  digitalWrite(NEOPIXEL_POWER, HIGH);
  #endif
  
  #ifdef USE_NEOPIXEL
  pixels = new Adafruit_NeoPixel(numLights, LED_PIN, NEO_GRB + NEO_KHZ800);

  Serial.begin(9600);
  pixels->begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels->setBrightness(LED_BRIGHTNESS); // not so bright
  #endif

  #ifdef USE_FASTLED
  fastleds = new CRGB[numLights];
  FastLED.addLeds<WS2812, LED_PIN, GRB>(fastleds, NUM_LEDS);
  #endif
}

///////////////////////////// set light by idx /////////////////////////////

void enoLedmapper::setLightByIdx(int  lightIdx, char lightColor, 
   int lightBrightness) {

  int color = ecm->getColorByKey(lightColor);
  int r, g, b;

  r = ecm->getR(color);
  g = ecm->getG(color);
  b = ecm->getB(color);

  #ifdef USE_FASTLED
  fastleds[lightIdx] = CRGB(r,g,b);
  #endif
  #ifdef USE_NEOPIXEL
  pixels.setPixelColor(lightIdx,
    pgm_read_byte(&gamma8[r]),
    pgm_read_byte(&gamma8[g]),
    pgm_read_byte(&gamma8[b]));
  #endif
}

///////////////////////////// show light /////////////////////////////

void enoLedmapper::showLight() {
  #ifdef USE_NEOPIXEL
  pixels.show();
  #endif
  #ifdef USE_FASTLED
  FastLED.show();
  #endif
}

/// end ///
