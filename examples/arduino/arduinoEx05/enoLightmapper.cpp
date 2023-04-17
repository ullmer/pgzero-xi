// Enodia lightmapper
// Brygg Ullmer, Clemson University
// Partial support from NSF CNS-1828611
// Begun 2023-04
// LLGPL3

#include <stdio.h>
#include <cstring>
#include "enoLightmapper.h"

////////////////////////// constructor //////////////////////////

enoLightmapper::enoLightmapper(int numLights, int whichChain, int maxBrightVal) {
  allocateLightBuffers(numLights);
  this->whichChain    = whichChain;
  this->maxBrightVal  = maxBrightVal;
  lightCursorIdx       = 0;
  nextLightmapperChunk = 0;
}

////////////////////////// allocate light buffers //////////////////////////

void enoLightmapper::allocateLightBuffers(int numLights) {
  this->numLights = numLights;
  lightKeys      = new char[numLights];
  lightColorKeys = new char[numLights];
  lightBright    = new int[ numLights];
  lightNames  = new const char*[numLights];
}
    
//////////////////////////  register light //////////////////////////

void enoLightmapper::registerLight(char lightKey, char lightColorKey, int lightIdx, const char lightName[], int lightBright) {
  if (lightIdx >= numLights) {return;} // need to handle better

  if (lightIdx == -1) {lightIdx = lightCursorIdx; lightCursorIdx++;}

  lightKeys[lightIdx]        = lightKey;
  lightColorKeys[lightIdx]   = lightColorKey;
  lightNames[lightIdx]       = lightName;
  this->lightBright[lightIdx] = lightBright;
}

//////////////////////////  getLightSummaryStr //////////////////////////

char *enoLightmapper::getLightSummaryStr() {
  int resultlen = 0;
  char **buffer = new char*[numLights];
  char lightNameBuffer[maxLightNameLen];
  char *currentLine;
  char *currentLight;

  for (int i=0; i<numLights; i++) {
    currentLine  = new char[maxCharsPerLine];
    int lightNameLen = strlen(lightNames[i]);

    if (lightNameLen > maxLightNameLen) { // avoid buffer overflow error
      currentLight = strncpy(lightNameBuffer, lightNames[i], maxLightNameLen);
    } else {
      currentLight = strcpy(lightNameBuffer, lightNames[i]);
    }
    
    //sprintf(currentLine, "%2i %c %2X %s\n", i, lightKeys[i], lightVals[i], currentLight); //could be refined further
    resultlen += strlen(currentLine);
    buffer[i] = currentLine;
  }

  char *result = new char[resultlen];

  int currentCharIdx = 0;
  for (int i=0; i<numLights; i++) {
    currentLine = buffer[i];
    strncpy(&result[currentCharIdx], currentLine, maxCharsPerLine);
    currentCharIdx += strlen(currentLine);
  }

  return result;
}

//////////////////////////  get light color by key //////////////////////////

int enoLightmapper::getLightIdxByKey(char lightKey) {
  for (int i=0; i<numLights; i++) {
    if (lightKey == lightKeys[i]) {
      return i;
    }
  }
  return -1; //probably not ideal, but a start
}

//////////////////////  get light color by key -- multiple returns ///////////

IntArr enoLightmapper::getLightIdxByKeyMulti(char lightKey) {

  int keyCount = 0;

  for (int i=0; i<numLights; i++) {
    if (lightKey == lightKeys[i]) {
      keyCount++;
    }
  }

  if (keyCount == 0) {return 0; //probably not ideal, but a start}

  IntArr iaResult = IntArr(keyCount);
}

//////////////////////////  get light color by key //////////////////////////

int enoLightmapper::getLightColByKey(char lightKey) {
  lightIdx = getLightIdxByKey(lightKey);
  if (lightIdx < 0) {return lightIdx;}
  int color = lightColorKeys[lightIdx];
  return color; 
}

//////////////////////////  get light color by index //////////////////////////

int enoLightmapper::getLightColByIdx(int  lightIdx) {
  return lightColorKeys[lightIdx];
}

//////////////////////////  get light idx by name //////////////////////////

int enoLightmapper::getLightIdxByName(char *lightName, bool caseSensitive) {

  int cmp;
  for (int i=0; i<numLights; i++) {
    if (caseSensitive) {cmp = strcmp(    lightName, lightNames[i]);}
    else               {cmp = strcasecmp(lightName, lightNames[i]);}

    if (cmp==0) {return i;}
  }
  return -1; 
}

//////////////////////////  get light idx by key //////////////////////////

int enoLightmapper::getLightIdxByKey(char lightKey) {
  for (int i=0; i<numLights; i++) {
    if (lightKey == lightKeys[i]) {return i;}
  }
  return -1;
}
    
////////////////////////// set light by name //////////////////////////

void enoLightmapper::setLightByName(char *lightName, char lightColor, int lightBrightness, bool caseSensitive) {
  int lightIdx = getLightIdxByName(lightName, caseSensitive);
  setLightByIdx(lightIdx, lightColor, lightBrightness);
}

////////////////////////// set light by key //////////////////////////

void enoLightmapper::setLightByKey(char lightKey, char lightColor, int lightBrightness, bool multikey) {
  if (!multikey) {
    int lightIdx = getLightIdxByKey(lightKey);
    setLightByIdx(lightIdx, lightColor, lightBrightness);

  } else {

    IntArr lightIdxs = getLightIdxByKeyMulti(lightKey);
    int liLen = lightIdxs.getSize();
    for (int i; i<liLen; i++) {
      int idx = lightIdxs[i];
      setLightByIdx(idx, lightColor, lightBrightness);
    }
  } 
}

////////////////////////// set light by idx //////////////////////////

//int enoLightmapper::setLightByIdx(int lightIdx, char lightColor, int lightBrightness) {
//}

/////////////////////////////////////////////////////////////////////////
///////////////////////////// integer array /////////////////////////////
/////////////////////////////////////////////////////////////////////////

///////////////////////////// constructor /////////////////////////////

IntArr::IntArr(int arrSize) {
  intArr = new int[arrSize];
  this->arrSize = arrSize;
}

///////////////////////////// getSize /////////////////////////////

int IntArr::getSize() {return arrSize;}
  
///////////////////////////// set elements /////////////////////////////

int IntArr::setEl(int idx, int val) {
  if (idx > arrSize) {return -1;}
  intArr[idx] = val;
}

int IntArr::setEls(int *array, int listLen) {
  if (listLen > arrSize) {return -1;}
  for (int i=0; i<listLen; i++) {
    intArr[i] = array[i];
  }

  return 1;
}

///////////////////////////// get elements /////////////////////////////

int IntArr::getEl(int idx) {
  if (idx >= arrSize) {return -1;} // consider an alternate implementation
  return intArr[idx];
}

int IntArr::operator[](int idx) {

  if (idx >= arrSize) {return -1;} // consider an alternate implementation
  return intArr[idx];
}

/// end ///
