// Enodia lightmapper
// Brygg Ullmer, Clemson University
// Partial support from NSF CNS-1828611
// Begun 2023-04
// LLGPL3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <cstring.h>
#include "enoLightmapper.h"

////////////////////////// constructor //////////////////////////

enoLightmapper::enoLightmapper(int numLights, enoColormapper *ecm, int whichChain, int maxBrightVal) {
  allocateLightBuffers(numLights);
  this->ecm           = ecm; //colormapper
  this->whichChain    = whichChain;
  this->maxBrightVal  = maxBrightVal;
  lightCursorIdx       = 0;
  nextLightmapperChunk = 0;
 
  helpHeader = "idx col brt key name\n";
  helpTempl  =   "%2i   %1c  %2X  %1c %s\n";
}

////////////////////////// allocate light buffers //////////////////////////

void enoLightmapper::allocateLightBuffers(int numLights) {
  this->numLights = numLights;
  lightKeys      = new char[numLights+1];
  lightColorKeys = new char[numLights+1];
  lightBright    = new int[ numLights];
  lightNames  = new const char*[numLights];

  for (int i=0; i<numLights; i++) {
    lightKeys[i]      = ' ';
    lightColorKeys[i] = ' ';
    lightBright[i]    = 0;
    lightNames[i]     = "";
  }
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

char *enoLightmapper::getLightSummaryStrCompact() {
  int i, endVal = numLights*2+2;
  char *resultStr = new char[endVal+1];

  for (i=0; i<numLights; i++) {
    resultStr[i] = lightColorKeys[i];	    
  }

  resultStr[i++] = '\r';
  resultStr[i++] = '\n';

  for (;i<endVal; i++) {resultStr[i] = '.';}
  resultStr[endVal] = 0; 

  return resultStr;
}

//////////////////////////  getLightSummaryStr //////////////////////////

char *enoLightmapper::getLightSummaryStr() {
  int resultlen = 0;

  int bufflen = numLights;
  if (showHelpHeader) {bufflen++;}

  char *buffer[bufflen];
  char lightNameBuffer[maxLightNameLen];
  char *currentLine;
  char *currentLight;
  int  buffIdx = 0;
  char *helpHeaderHandle;

  if (showHelpHeader) {
    helpHeaderHandle = strdup(helpHeader); // workaround casting issue
    buffer[0] = helpHeaderHandle;
    resultlen += strlen(buffer[0]);
    buffIdx += 1;
  }
  for (int i=0; i<numLights; i++) {
    char *currentLine = new char[maxCharsPerLine];
    int lightNameLen = strlen(lightNames[i]);

    if (lightNameLen > maxLightNameLen) {
      // buffer overflow errors are problematic 
      currentLight = strncpy(lightNameBuffer, lightNames[i], 
                             maxLightNameLen);
    } else {
      currentLight = strcpy(lightNameBuffer, lightNames[i]);
    }
    
    //helpHeader = "idx col brt key name\n";
    //helpTempl  =   "%2i   %1c  %2X  %1c %s\n";

    sprintf(currentLine, helpTempl, i, lightColorKeys[i], lightBright[i], 
            lightKeys[i], lightNames[i]);

    resultlen += strlen(currentLine);
    buffer[buffIdx] = currentLine;
    buffIdx++;
  }

  char *result = new char[resultlen+1];
  int currentCharIdx = 0;

  for (int i=0; i<buffIdx; i++) {
    currentLine = buffer[i];
    int currentLineLen = strlen(currentLine);
    
    int bytesToCopy;
    if (currentLineLen < maxCharsPerLine) { bytesToCopy = currentLineLen;}
    else                                  { bytesToCopy = maxCharsPerLine;}
    memcpy(&(result[currentCharIdx]), currentLine, bytesToCopy);
    currentCharIdx += bytesToCopy;
  }
  result[resultlen]=0;

  if (helpHeaderHandle != 0) {free(helpHeaderHandle);} 

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

  if (keyCount == 0) {return 0;} //probably not ideal, but a start

  IntArr iaResult = IntArr(keyCount);

  int keyIdx = 0;

  for (int i=0; i<numLights; i++) {
    if (lightKey == lightKeys[i]) {
      iaResult.setEl(keyIdx, i); keyIdx++;
    }
  }

  return iaResult;
}

//////////////////////////  get light color by key //////////////////////////

int enoLightmapper::getLightColByKey(char lightKey) {
  int lightIdx = getLightIdxByKey(lightKey);
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

//int enoLightmapper::getLightIdxByKey(char lightKey) {
//  for (int i=0; i<numLights; i++) {
//    if (lightKey == lightKeys[i]) {return i;}
//  }
//  return -1;
//}
    
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
  return 1;
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
