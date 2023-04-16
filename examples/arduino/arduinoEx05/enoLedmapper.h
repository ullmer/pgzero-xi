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
    enoLEDmapper(int numLEDs, int whichChain=0, int maxBrightVal=10);
    void allocateLedBuffers(int numLEDs);
    void registerLED(char ledKey, char ledColorKey, int ledIdx=-1, 
                     const char ledName[]="", int ledBright=5); //-1 = next in sequence

    char  *getLEDSummaryStr();
    char  *getLEDYamlStr();
    int    getLEDByKey(char ledKey);
    int    getLEDByIdx(int  ledIdx);
    int    getLEDByName( char *ledName, bool caseSensitive=false);
    
  private:
    int  whichChain;
    char *ledKeys      = NULL;
    char *ledColorKeys = NULL;
    char *ledBright    = NULL;
    const char **ledNames; // may benefit from revisiting
    int numLED;
    int maxLEDkeysPerChunk;
    int maxLEDNameLen = 15; 
    int maxBrightVal  = 10; 
    int maxCharsPerLine = 82; //80 + CRLF
    enoLEDmapper *nextLEDmapperChunk;
};

// end //
