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

    char *getLEDSummaryStr();
    char *getLEDYamlStr();

    int getLEDColByKey(char ledKey);
    int getLEDColByIdx(int  ledIdx);
    int getLEDColByName(char *ledName, bool caseSensitive=false);
    int getLEDIdxByName(char *ledName, bool caseSensitive=false);
    
    int setLEDByKey(char ledKey, char ledColor, int ledBrightness);
    int setLEDByIdx(int  ledIdx, char ledColor, int ledBrightness);
    int setLEDByName(char *ledName, char ledColor, int ledBrightness, bool caseSensitive=false);
    
  private:
    int  whichChain;
    char *ledKeys      = NULL;
    char *ledColorKeys = NULL;
    char *ledBright    = NULL;
    const char **ledNames; // may benefit from revisiting
    int numLEDs;
    int ledCursorIdx  = 0;
    int maxLEDNameLen = 15; 
    int maxBrightVal  = 10; 
    int maxCharsPerLine = 82; //80 + CRLF
    enoLEDmapper *nextLEDmapperChunk;
};

// end //
