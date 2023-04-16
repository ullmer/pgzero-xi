// Enodia colormapper
// Brygg Ullmer, Clemson University
// Partial support from NSF CNS-1828611
// Begun 2023-04
// LLGPL3

#ifndef enoColormapper_h
#define enoColormapper_h
#endif

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
    
  private:
    char  *colorKeys = nullptr;
    int   *colorVals = nullptr;
    const char **colorNames = nullptr; // may benefit from revisiting
    int numColorkeysUsed;
    int maxColorkeysPerChunk;
    int maxCharsPerLine = 82; //80 + CRLF
    int maxColorNameLen = 15; 
    enoColormapper *nextColormapperChunk;
};

// end //
