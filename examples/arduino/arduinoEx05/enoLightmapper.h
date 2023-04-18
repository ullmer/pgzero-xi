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

    char *getLightSummaryStrCompact();
    char *getLightSummaryStr();
    char *getLightYamlStr();

    int    getLightColByKey(     char lightKey);
    int    getLightIdxByKey(     char lightKey);
    IntArr getLightIdxByKeyMulti(char lightKey);

    int getLightColByIdx(int  lightIdx);
    int getLightColByName(char *lightName, bool caseSensitive=false);
    int getLightIdxByName(char *lightName, bool caseSensitive=false);
    
    void setLightByKey(char lightKey, char lightColor, int lightBrightness, 
                       bool multikey=true);

    void setLightByName(char *lightName, char lightColor, 
                        int lightBrightness, bool caseSensitive=false);

    // virtual functions, allowing for different implementation for 
    // different tech (with different extant implementational calls)
    
    virtual void setLightByIdx(int  lightIdx, char lightColor, 
                               int lightBrightness) = 0;

    virtual void showLight() = 0;
    
  protected:
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

    const static bool showHelpHeader = true;
    const char *helpHeader; // "idx col brt key name";
    const char *helpTempl;  // "%2i %1c %2X %1c %s\n";
};

///////////////////////////// integer array /////////////////////////////

class IntArr {
  public:
    IntArr (int arrSize);
    int getSize();
    int setEls(int *list, int listLen);
    int setEl(int idx, int val);
    int getEl(int idx);
    int operator[](int idx);
 
  private:
    int *intArr;
    int arrSize;
};

/// end ///
