// Enodia LED mapper
// Brygg Ullmer, Clemson University
// Partial support from NSF CNS-1828611
// Begun 2023-04
// LLGPL3

#ifndef enoLEDmapper_h
#define enoLEDmapper_h
#endif

#define ECM_DEFAULT_LEDCHUNK 10

class enoLEDmapper {
  public:
    enoLEDmapper(int maxLEDkeysPerChunk=ECM_DEFAULT_LEDCHUNK, bool generateStandardLEDs=true);
    void allocateBuffers(int numLEDkeys);
    void registerLED(char ledKey, const char ledName[], int ledVal);

    char  *getLEDSummaryStr();
    int    getLEDByKey(char ledKey);
    int    getLEDByIdx(int  ledIdx);
    int    getLEDByName(char *ledName, bool caseSensitive=false);
    
  private:
    char  *ledKeys;
    const char **ledNames; // may benefit from revisiting
    int   *ledVals;
    int numLEDkeysUsed;
    int maxLEDkeysPerChunk;
    int maxLEDNameLen = 15; 
    int maxCharsPerLine = 82; //80 + CRLF
    enoLEDmapper *nextLEDmapperChunk;
};

// end //
