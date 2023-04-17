// Enodia LED mapper
// Brygg Ullmer, Clemson University
// Partial support from NSF CNS-1828611
// Begun 2023-04
// LLGPL3

#include "enoStrLightmapper.h"

///////////////////////////// constructor /////////////////////////////

enoStrLightmapper::enoStrLightmapper(int numLights, int whichChain=0, 
  int maxBrightVal=10) : enoLightmapper(numLights, whichChain, maxBrightVal) {

}

///////////////////////////// set light by idx /////////////////////////////

void enoStrLightmapper::setLightByIdx(int  lightIdx, char lightColor, 
   int lightBrightness) {

  pixels.setPixelColor(pixelNumber,
    pgm_read_byte(&gamma8[r]),
    pgm_read_byte(&gamma8[g]),
    pgm_read_byte(&gamma8[b]));
}

///////////////////////////// show light /////////////////////////////

void enoStrLightmapper::showLight();
  printf("enoStrLight mapper :: showLight\n");
}

/// end ///
