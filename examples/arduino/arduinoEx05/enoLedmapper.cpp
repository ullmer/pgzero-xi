// Enodia ledmapper
// Brygg Ullmer, Clemson University
// Partial support from NSF CNS-1828611
// Begun 2023-04
// LLGPL3

#include <stdio.h>
#include <cstring>
#include "enoLEDmapper.h"

////////////////////////// constructor //////////////////////////

enoLEDmapper::enoLEDmapper(int numLEDs, int whichChain, int maxBrightVal);
  allocateLedBuffers(numLEDs);
  this.whichChain    = whichChain;
  this.maxBrightVal  = maxBrightVal;
  nextLEDmapperChunk = NULL;
}

////////////////////////// allocate buffers //////////////////////////

void enoLEDmapper::allocateBuffers(int numLEDkeys) {
  maxLEDkeysPerChunk = numLEDkeys;
  ledKeys  = new  char[numLEDkeys];
  ledVals  = new   int[numLEDkeys];
  ledNames = new const char*[numLEDkeys];
  numLEDkeysUsed = 0;
}

//////////////////////////  register led //////////////////////////
    void registerLED(

void enoLEDmapper::registerLED(char ledKey, char ledColorKey, int ledIdx, const char ledName[], int ledBright) {
  if (numLEDkeysUsed >= maxLEDkeysPerChunk) {return;} // need to handle better

  ledKeys[numLEDkeysUsed]  = ledKey;
  ledNames[numLEDkeysUsed] = ledName;
  ledVals[numLEDkeysUsed]  = ledVal;
  numLEDkeysUsed++;
}


//////////////////////////  getLEDSummaryStr //////////////////////////

char *enoLEDmapper::getLEDSummaryStr() {
  int resultlen = 0;
  char **buffer = new char*[numLEDkeysUsed];
  char ledNameBuffer[maxLEDNameLen];
  char *currentLine;
  char *currentLED;

  for (int i=0; i<numLEDkeysUsed; i++) {
    currentLine  = new char[maxCharsPerLine];
    int ledNameLen = strlen(ledNames[i]);

    if (ledNameLen > maxLEDNameLen) { // avoid buffer overflow error
      currentLED = strncpy(ledNameBuffer, ledNames[i], maxLEDNameLen);
    } else {
      currentLED = strcpy(ledNameBuffer, ledNames[i]);
    }
    
    sprintf(currentLine, "%2i %c %6X %s\n", i, ledKeys[i], ledVals[i], currentLED); //could be refined further
    resultlen += strlen(currentLine);
    buffer[i] = currentLine;
  }

  char *result = new char[resultlen];

  int currentCharIdx = 0;
  for (int i=0; i<numLEDkeysUsed; i++) {
    currentLine = buffer[i];
    strncpy(&result[currentCharIdx], currentLine, maxCharsPerLine);
    currentCharIdx += strlen(currentLine);
  }

  return result;
}

//////////////////////////  get led by key //////////////////////////

int  enoLEDmapper::getLEDByKey(char ledKey) {
  for (int i=0; i<numLEDkeysUsed; i++) {
    if (ledKey == ledKeys[i]) {
      return ledVals[i];
    }
  }
  return 0; //probably not ideal, but a start
}

//////////////////////////  get led by key //////////////////////////

int   enoLEDmapper::getLEDByIdx(int  ledIdx) {
  return ledVals[ledIdx];
}

//////////////////////////  get led by key //////////////////////////

int   enoLEDmapper::getLEDByName(char *ledName, bool caseSensitive) {

  int cmp;
  for (int i=0; i<numLEDkeysUsed; i++) {
    if (caseSensitive) {cmp = strcmp(    ledName, ledNames[i]);}
    else               {cmp = strcasecmp(ledName, ledNames[i]);}

    if (cmp==0) {return ledVals[i];}
  }
  return 0; //probably not ideal, but a start
}
    
// end //
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
