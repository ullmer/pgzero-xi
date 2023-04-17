// Enodia LED mapper
// Brygg Ullmer, Clemson University
// Partial support from NSF CNS-1828611
// Begun 2023-04
// LLGPL3

#ifndef enoLedmapper_h
#define enoLedmapper_h
#endif

#include "enoLightmapper.h"

///////////////////////////// Enodia Light Mapper /////////////////////////////

class enoLedmapper : public enoLightmapper {
  public:
    enoLedmapper(int numLights, int whichChain=0, int maxBrightVal=10);
    void setLightByIdx(int  lightIdx, char lightColor, int lightBrightness);
};

/// end ///
