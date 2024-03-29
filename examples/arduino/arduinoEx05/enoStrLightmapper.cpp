// Enodia LED mapper
// Brygg Ullmer, Clemson University
// Partial support from NSF CNS-1828611
// Begun 2023-04
// LLGPL3

#include "enoStrLightmapper.h"

///////////////////////////// constructor /////////////////////////////

enoStrLightmapper::enoStrLightmapper(int numLights, int whichChain, 
  int maxBrightVal) : enoLightmapper(numLights, whichChain, maxBrightVal) {

  printf("enoStrLight mapper :: constructor called\n");
}

///////////////////////////// set light by idx /////////////////////////////

void enoStrLightmapper::setLightByIdx(int  lightIdx, char lightColor, 
   int lightBrightness) {

  printf("enoStrLight mapper :: set light by index :: idx %i, col %c, brt %i\n",
         lightIdx, lightColor, lightBrightness);

  if (lightIdx > numLights) {
    printf("enoStrLightmapper setLightByIdx error: idx > numLights!\n");
    return;
  }

  lightColorKeys[lightIdx] = lightColor;
  lightBright[lightIdx]    = lightBrightness;
}

///////////////////////////// show light /////////////////////////////

void enoStrLightmapper::showLight() {
  printf("enoStrLight mapper :: showLight\n");
}

/// end ///
