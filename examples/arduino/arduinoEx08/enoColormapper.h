// Enodia colormapper
// Brygg Ullmer, Clemson University
// Partial support from NSF CNS-1828611
// Begun 2023-04
// LLGPL3

#ifndef enoColormapper_h
#define enoColormapper_h

#define ECM_DEFAULT_COLORCHUNK 10

class enoColormapper {
  public:
    enoColormapper(int maxColorkeysPerChunk=ECM_DEFAULT_COLORCHUNK, bool generateStandardColors=true);
    void allocateBuffers(int numColorkeys);
    void registerColor(char colorKey, const char colorName[], int colorVal);

    char  *getColorSummaryStr();
    char  *getColorYamlStr();
    void   populateStandardColors();

    int    getColorByKey(char colorKey);
    int    getColorByIdx(int  colorIdx);
    int    getColorByName(char *colorName, bool caseSensitive=false);

    int    getR(int color) {int result = color & 0xff0000; result >>= 16; return result;}
    int    getG(int color) {int result = color & 0xff00;   result >>= 8;  return result;}
    int    getB(int color) {int result = color & 0xff;                    return result;}
    
  private:
    char  *colorKeys;
    int   *colorVals;
    const char **colorNames; 
    int numColorkeysUsed;
    int maxColorkeysPerChunk;
    static const int maxCharsPerLine = 82; //80 + CRLF
    static const int maxColorNameLen = 15; 
    enoColormapper *nextColormapperChunk;
};

#endif
// end //
