// Enodia lightmapper
// Brygg Ullmer, Clemson University
// Partial support from NSF CNS-1828611
// Begun 2023-04
// LLGPL3

#include <stdio.h>
#include <cstring>
#include "enoLightmapper.h"

////////////////////////// constructor //////////////////////////

enoLightmapper::enoLightmapper(int numLights, int whichChain, int maxBrightVal);
  allocateLightBuffers(numLights);
  this.whichChain    = whichChain;
  this.maxBrightVal  = maxBrightVal;
  nextLightmapperChunk = NULL;
}

////////////////////////// allocate light buffers //////////////////////////

void enoLightmapper::allocateLightBuffers(int numLights) {
  this.numLights = numLights;
  lightKeys   = new char[numLights];
  lightVals   = new char[numLights];
  lightBright = new int[ numLights];
  lightNames  = new const char*[numLights];
}
    
//////////////////////////  register light //////////////////////////

void enoLightmapper::registerLight(char lightKey, char lightColorKey, int lightIdx, const char lightName[], int lightBright) {
  if (numLightkeysUsed >= maxLightkeysPerChunk) {return;} // need to handle better

  if (lightIdx == -1) {lightIdx = lightCursorIdx; lightCursorIdx++;}

  lightKeys[lightIdx]        = lightKey;
  lightColorKeys[lightIdx]   = lightColorKey;
  lightNames[lightIdx]       = lightName;
  this.lightBright[lightIdx] = lightBright;
}

//////////////////////////  getLightSummaryStr //////////////////////////

char *enoLightmapper::getLightSummaryStr() {
  int resultlen = 0;
  char **buffer = new char*[numLightkeysUsed];
  char lightNameBuffer[maxLightNameLen];
  char *currentLine;
  char *currentLight;

  for (int i=0; i<numLightkeysUsed; i++) {
    currentLine  = new char[maxCharsPerLine];
    int lightNameLen = strlen(lightNames[i]);

    if (lightNameLen > maxLightNameLen) { // avoid buffer overflow error
      currentLight = strncpy(lightNameBuffer, lightNames[i], maxLightNameLen);
    } else {
      currentLight = strcpy(lightNameBuffer, lightNames[i]);
    }
    
    sprintf(currentLine, "%2i %c %2X %s\n", i, lightKeys[i], lightVals[i], currentLight); //could be refined further
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

//////////////////////////  get light color by key //////////////////////////

int enoLightmapper::getLightColByKey(char lightKey) {
  for (int i=0; i<numLightkeysUsed; i++) {
    if (lightKey == lightKeys[i]) {
      return lightColorKeys[i];
    }
  }
  return 0; //probably not ideal, but a start
}

//////////////////////////  get light color by index //////////////////////////

int enoLightmapper::getLightColByIdx(int  lightIdx) {
  return lightColorKeys[lightIdx];
}

//////////////////////////  get light idx by name //////////////////////////

int enoLightmapper::getLightIdxByName(char *lightName, bool caseSensitive) {

  int cmp;
  for (int i=0; i<numLightkeysUsed; i++) {
    if (caseSensitive) {cmp = strcmp(    lightName, lightNames[i]);}
    else               {cmp = strcasecmp(lightName, lightNames[i]);}

    if (cmp==0) {return i;}
  }
  return -1; 
}

//////////////////////////  get light idx by key //////////////////////////

int enoLightmapper::getLightIdxByKey(char lightKey) {
  for (int i=0; i<numLightkeysUsed; i++) {
    if (lightKey == lightKeys[i]) {return i;}
  }
  return -1;
}
    
////////////////////////// set light by name //////////////////////////

int enoLightmapper::setLightByName(char *lightName, char lightColor, int lightBrightness, bool caseSensitive) {
  int lightIdx = getLightIdxByName(lightName, caseSensitive);
  setLightByIdx(lightIdx, lightColor, lightBrightness);
}

////////////////////////// set light by key //////////////////////////

int enoLightmapper::setLightByKey(char lightKey, char lightColor, int lightBrightness, bool multikey) {
  if (!multikey()) {
    int lightIdx = getLightIdxByKey(lightKey);
    setLightByIdx(lightIdx, lightColor, lightBrightness);
  } else {
    int lightIdx[] = getLightIdxByKeyMulti(lightKey);
    l
    
}

////////////////////////// set light by idx //////////////////////////

int enoLightmapper::setLightByIdx(int lightIdx, char lightColor, int lightBrightness) {
}

// end //
