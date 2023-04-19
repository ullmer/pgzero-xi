// Enodia LED mapper
// Brygg Ullmer, Clemson University
// Partial support from NSF CNS-1828611
// Begun 2023-04
// LLGPL3

#include <Adafruit_NeoPixel.h>
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
  
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.setBrightness(7); // not so bright
}

///////////////////////////// set light by idx /////////////////////////////

void enoLedmapper::setLightByIdx(int  lightIdx, char lightColor, 
   int lightBrightness) {

  int color = ecm->getColorByKey();
  int r, g, b;

  r = ecm->getR(color);
  g = ecm->getG(color);
  b = ecm->getB(color);

  pixels.setPixelColor(lightIdx,
    pgm_read_byte(&gamma8[r]),
    pgm_read_byte(&gamma8[g]),
    pgm_read_byte(&gamma8[b]));
}

///////////////////////////// show light /////////////////////////////

void enoLedmapper::showLight();
  pixels.show();
}

/// end ///
