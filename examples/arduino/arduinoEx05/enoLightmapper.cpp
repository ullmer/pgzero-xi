// Enodia ledmapper
// Brygg Ullmer, Clemson University
// Partial support from NSF CNS-1828611
// Begun 2023-04
// LLGPL3

#include <stdio.h>
#include <cstring>
#include "enoLightmapper.h"

////////////////////////// constructor //////////////////////////

enoLightmapper::enoLightmapper(int numLights, int whichChain, int maxBrightVal);
  allocateLedBuffers(numLights);
  this.whichChain    = whichChain;
  this.maxBrightVal  = maxBrightVal;
  nextLightmapperChunk = NULL;
}

////////////////////////// allocate led buffers //////////////////////////

void enoLightmapper::allocateLedBuffers(int numLights) {
  this.numLights = numLights;
  ledKeys   = new char[numLights];
  ledVals   = new char[numLights];
  ledBright = new int[ numLights];
  ledNames  = new const char*[numLights];
}
    
//////////////////////////  register led //////////////////////////

void enoLightmapper::registerLight(char ledKey, char ledColorKey, int ledIdx, const char ledName[], int ledBright) {
  if (numLightkeysUsed >= maxLightkeysPerChunk) {return;} // need to handle better

  if (ledIdx == -1) {ledIdx = ledCursorIdx; ledCursorIdx++;}

  ledKeys[ledIdx]        = ledKey;
  ledColorKeys[ledIdx]   = ledColorKey;
  ledNames[ledIdx]       = ledName;
  this.ledBright[ledIdx] = ledBright;
}

//////////////////////////  getLightSummaryStr //////////////////////////

char *enoLightmapper::getLightSummaryStr() {
  int resultlen = 0;
  char **buffer = new char*[numLightkeysUsed];
  char ledNameBuffer[maxLightNameLen];
  char *currentLine;
  char *currentLight;

  for (int i=0; i<numLightkeysUsed; i++) {
    currentLine  = new char[maxCharsPerLine];
    int ledNameLen = strlen(ledNames[i]);

    if (ledNameLen > maxLightNameLen) { // avoid buffer overflow error
      currentLight = strncpy(ledNameBuffer, ledNames[i], maxLightNameLen);
    } else {
      currentLight = strcpy(ledNameBuffer, ledNames[i]);
    }
    
    sprintf(currentLine, "%2i %c %2X %s\n", i, ledKeys[i], ledVals[i], currentLight); //could be refined further
    resultlen += strlen(currentLine);
    buffer[i] = currentLine;
  }

  char *result = new char[resultlen];

  int currentCharIdx = 0;
  for (int i=0; i<numLightkeysUsed; i++) {
    currentLine = buffer[i];
    strncpy(&result[currentCharIdx], currentLine, maxCharsPerLine);
    currentCharIdx += strlen(currentLine);
  }

  return result;
}

//////////////////////////  get led color by key //////////////////////////

int enoLightmapper::getLightColByKey(char ledKey) {
  for (int i=0; i<numLightkeysUsed; i++) {
    if (ledKey == ledKeys[i]) {
      return ledColorKeys[i];
    }
  }
  return 0; //probably not ideal, but a start
}

//////////////////////////  get led color by index //////////////////////////

int enoLightmapper::getLightColByIdx(int  ledIdx) {
  return ledColorKeys[ledIdx];
}

//////////////////////////  get led idx by name //////////////////////////

int enoLightmapper::getLightIdxByName(char *ledName, bool caseSensitive) {

  int cmp;
  for (int i=0; i<numLightkeysUsed; i++) {
    if (caseSensitive) {cmp = strcmp(    ledName, ledNames[i]);}
    else               {cmp = strcasecmp(ledName, ledNames[i]);}

    if (cmp==0) {return i;}
  }
  return -1; 
}

//////////////////////////  get led idx by key //////////////////////////

int enoLightmapper::getLightIdxByKey(char ledKey) {
  for (int i=0; i<numLightkeysUsed; i++) {
    if (ledKey == ledKeys[i]) {return i;}
  }
  return -1;
}
    
////////////////////////// set led by name //////////////////////////

int enoLightmapper::setLightByName(char *ledName, char ledColor, int ledBrightness, bool caseSensitive) {
  int ledIdx = getLightIdxByName(ledName, caseSensitive);
  setLedByIdx(ledIdx, ledColor, ledBrightness);
}

////////////////////////// set led by key //////////////////////////

int enoLightmapper::setLightByKey(char ledKey, char ledColor, int ledBrightness) {
  int ledIdx = getLightIdxByKey(ledKey);
  setLedByIdx(ledIdx, ledColor, ledBrightness);
}

////////////////////////// set led by idx //////////////////////////

int enoLightmapper::setLightByIdx(int ledIdx, char ledColor, int ledBrightness) {
}

// end //
