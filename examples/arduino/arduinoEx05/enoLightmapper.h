// Enodia Light mapper
// Brygg Ullmer, Clemson University
// Partial support from NSF CNS-1828611
// Begun 2023-04
// LLGPL3

#ifndef enoLightmapper_h
#define enoLightmapper_h
#endif

#define ECM_DEFAULT_LightCHUNK 10

///////////////////////////// Enodia Light Mapper /////////////////////////////

class enoLightmapper {
  public:
    enoLightmapper(int numLights, int whichChain=0, int maxBrightVal=10);
    void allocateLightBuffers(int numLights);
    void registerLight(char lightKey, char lightColorKey, int lightIdx=-1, 
                     const char lightName[]="", int lightBright=5); //-1 = next in sequence

    char *getLightSummaryStr();
    char *getLightYamlStr();

    int getLightColByKey(char lightKey);
    int getLightColByIdx(int  lightIdx);
    int getLightColByName(char *lightName, bool caseSensitive=false);
    int getLightIdxByName(char *lightName, bool caseSensitive=false);
    
    int setLightByKey(char lightKey, char lightColor, int lightBrightness, bool multikey=true);
    int setLightByIdx(int  lightIdx, char lightColor, int lightBrightness);
    int setLightByName(char *lightName, char lightColor, int lightBrightness, bool caseSensitive=false);
    
  private:
    int  whichChain;
    char *lightKeys      = NULL;
    char *lightColorKeys = NULL;
    char *lightBright    = NULL;
    const char **lightNames; // may benefit from revisiting
    int numLights;
    int lightCursorIdx  = 0;
    int maxLightNameLen = 15; 
    int maxBrightVal  = 10; 
    int maxCharsPerLine = 82; //80 + CRLF
    enoLightmapper *nextLightmapperChunk;
};

///////////////////////////// integer array /////////////////////////////

class IntArr {
  public:
    IntArr (int arrSize);
    int getSize();
    int setEls(int *list, int listLen);
    int getEl(int idx);
 
  private:
    int *intArr;
    int arrSize;
}

/// end ///
