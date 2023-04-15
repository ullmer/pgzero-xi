// Enodia colormapper
// Brygg Ullmer, Clemson University
// Partial support from NSF CNS-1828611
// Begun 2023-04
// LLGPL3

#include "enoColormapper.h"

////////////////////////// constructor //////////////////////////

enoColormapper::enoColormapper(int maxColorkeysPerChunk) {
  allocateBuffers(maxColorkeysPerChunk);
  nextColormapperChunk = null;
}

////////////////////////// allocate buffers //////////////////////////

int   enoColormapper::allocateBuffers(int numColorkeys) {
  maxColorkeysPerChunk = numColorkeys;
  colorKeys  = new   char[numColorkeys];
  colorNames = new String[numColorkeys];
  colorVals  = new    int[numColorkeys];
  numColorkeysUsed = 0;
}

//////////////////////////  register color //////////////////////////

int enoColormapper::registerColor(char colorKey, String colorName, int colorVal) {
  if (numColorskeysUsed >= maxColorkeysPerChunk) {return;} // need to handle better

  idx = numColorkeysUsed; numColorkeysUsed++;

  colorKeys[idx]  = colorKey;
  colorNames[idx] = colorName;
  colorVals[idx]  = colorVal;
}

//////////////////////////  getColorSummaryStr //////////////////////////

String enoColormapper::getColorSummaryStr() {
   

}


    int   getColorByKey(char colorKey);
    int   getColorByIdx(int  colorIdx);
    int   getColorByName(char *colorName, bool caseSensitive=false);
    
  private:
    char  *colorKeys;
    char **colorNames;
    int   *colorVals;
    int numColorskeysUsed;
    int maxColorkeysPerChunk;
    enoColormapper *nextColormapperChunk;
}

// end //