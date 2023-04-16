// Enodia Light mapper
// Brygg Ullmer, Clemson University
// Partial support from NSF CNS-1828611
// Begun 2023-04
// LLGPL3

#ifndef enoLightmapper_h
#define enoLightmapper_h
#endif

#define ECM_DEFAULT_LightCHUNK 10

class enoLightmapper {
  public:
    enoLightmapper(int numLights, int whichChain=0, int maxBrightVal=10);
    void allocateLedBuffers(int numLights);
    void registerLight(char ledKey, char ledColorKey, int ledIdx=-1, 
                     const char ledName[]="", int ledBright=5); //-1 = next in sequence

    char *getLightSummaryStr();
    char *getLightYamlStr();

    int getLightColByKey(char ledKey);
    int getLightColByIdx(int  ledIdx);
    int getLightColByName(char *ledName, bool caseSensitive=false);
    int getLightIdxByName(char *ledName, bool caseSensitive=false);
    
    int setLightByKey(char ledKey, char ledColor, int ledBrightness);
    int setLightByIdx(int  ledIdx, char ledColor, int ledBrightness);
    int setLightByName(char *ledName, char ledColor, int ledBrightness, bool caseSensitive=false);
    
  private:
    int  whichChain;
    char *ledKeys      = NULL;
    char *ledColorKeys = NULL;
    char *ledBright    = NULL;
    const char **ledNames; // may benefit from revisiting
    int numLights;
    int ledCursorIdx  = 0;
    int maxLightNameLen = 15; 
    int maxBrightVal  = 10; 
    int maxCharsPerLine = 82; //80 + CRLF
    enoLightmapper *nextLightmapperChunk;
};

// end //
