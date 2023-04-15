// Enodia colormapper
// Brygg Ullmer, Clemson University
// Partial support from NSF CNS-1828611
// Begun 2023-04
// LLGPL3

#include "enoColormapper.h"

////////////////////////// constructor //////////////////////////

enoColormapper(int maxColorkeysPerChunk) {
  allocateBuffers(maxColorkeysPerChunk);
  nextColormapperChunk = null;
}

////////////////////////// constructor //////////////////////////

int   allocateBuffers(int numColorkeys) {
  maxColorkeysPerChunk = numColorkeys;
  colorKeys  = new char[numColorkeys];
  colorNames = new char*[numColorkeys];
  colorVals  = new int[numColorkeys];
  numColorkeysUsed = 0;
}


    int   registerColor(char colorKey, char *colorName, int colorVal);

    char *getColorSummaryStr();
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
