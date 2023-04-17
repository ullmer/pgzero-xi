// Enodia Light mapper
// Brygg Ullmer, Clemson University
// Partial support from NSF CNS-1828611
// Begun 2023-04
// LLGPL3

#ifndef enoLightmapper_h
#define enoLightmapper_h
#endif

#define ECM_DEFAULT_LightCHUNK 10

class IntArr; //forward declaration; at bottom, as details aren't of highest relevance

///////////////////////////// Enodia Light Mapper /////////////////////////////

class enoLightmapper {
  public:
    enoLightmapper(int numLights, int whichChain=0, int maxBrightVal=10);
    void allocateLightBuffers(int numLights);
    void registerLight(char lightKey, char lightColorKey, int lightIdx=-1, 
                     const char lightName[]="", int lightBright=5); //-1 = next in sequence

    char *getLightSummaryStr();
    char *getLightYamlStr();

    int    getLightColByKey(     char lightKey);
    IntArr getLightColByKeyMulti(char lightKey);

    int getLightColByIdx(int  lightIdx);
    int getLightColByName(char *lightName, bool caseSensitive=false);
    int getLightIdxByName(char *lightName, bool caseSensitive=false);
    
    void setLightByKey(char lightKey, char lightColor, int lightBrightness, bool multikey=true);
    void setLightByIdx(int  lightIdx, char lightColor, int lightBrightness);
    void setLightByName(char *lightName, char lightColor, int lightBrightness, bool caseSensitive=false);
    
  private:
    int  whichChain;
    char *lightKeys;
    char *lightColorKeys;
    int  *lightBright;

    const char **lightNames; // may benefit from revisiting

    int numLights;
    int lightCursorIdx;
    const static int maxLightNameLen = 15; 
    int maxBrightVal; 
    const static int maxCharsPerLine = 82; //80 + CRLF
    enoLightmapper *nextLightmapperChunk;
};

///////////////////////////// integer array /////////////////////////////

class IntArr {
  public:
    IntArr (int arrSize);
    int getSize();
    int setEls(int *list, int listLen);
    int getEl(int idx);
    int operator[](int idx);
 
  private:
    int *intArr;
    int arrSize;
};

/// end ///
