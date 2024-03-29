// Enodia LED mapper
// Brygg Ullmer, Clemson University
// Partial support from NSF CNS-1828611
// Begun 2023-04
// LLGPL3

#ifndef enoStrLightmapper_h
#define enoStrLightmapper_h
#endif

#include <stdio.h>
#include "enoColormapper.h"
#include "enoLightmapper.h"

///////////////////////////// Enodia Light Mapper /////////////////////////////

class enoStrLightmapper : public enoLightmapper {
  public:
    enoStrLightmapper(int numLights, enoColormapper *ecm, int whichChain=0, int maxBrightVal=10);
  
    void setLightByIdx(int lightIdx, char lightColor, int lightBrightness);
    void showLight();
};

 ///end///
