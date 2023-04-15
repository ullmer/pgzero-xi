// Enodia colormapper
// Brygg Ullmer, Clemson University
// Partial support from NSF CNS-1828611
// Begun 2023-04
// LLGPL3

#ifndef enoColormapper_h
#define enoColormapper_h
#endif

class enoColormapper {
  public:
    enoColormapper(int maxColorkeysPerChunk);
    int   allocateBuffers(int numColorkeys);
    int   registerColor(char colorKey, char *colorName, int colorVal);

    char  *getColorSummaryStr();
    int    getColorByKey(char colorKey);
    int    getColorByIdx(int  colorIdx);
    int    getColorByName(char *colorName, bool caseSensitive=false);
    
  private:
    char  *colorKeys;
    char **colorNames;
    int   *colorVals;
    int numColorkeysUsed;
    int maxColorkeysPerChunk;
    int maxCharsPerLine = 82; //80 + CRLF
    enoColormapper *nextColormapperChunk;
}

// end //
