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

////////////////////////// allocate led buffers //////////////////////////

void enoLEDmapper::allocateLedBuffers(int numLEDs) {
  this.numLEDs = numLEDs;
  ledKeys   = new char[numLEDs];
  ledVals   = new char[numLEDs];
  ledBright = new int[ numLEDs];
  ledNames  = new const char*[numLEDs];
}
    
//////////////////////////  register led //////////////////////////

void enoLEDmapper::registerLED(char ledKey, char ledColorKey, int ledIdx, const char ledName[], int ledBright) {
  if (numLEDkeysUsed >= maxLEDkeysPerChunk) {return;} // need to handle better

  if (ledIdx == -1) {ledIdx = ledCursorIdx; ledCursorIdx++;}

  ledKeys[ledIdx]        = ledKey;
  ledColorKeys[ledIdx]   = ledColorKey;
  ledNames[ledIdx]       = ledName;
  this.ledBright[ledIdx] = ledBright;
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
    
    sprintf(currentLine, "%2i %c %2X %s\n", i, ledKeys[i], ledVals[i], currentLED); //could be refined further
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

//////////////////////////  get led color by key //////////////////////////

int enoLEDmapper::getLEDColByKey(char ledKey) {
  for (int i=0; i<numLEDkeysUsed; i++) {
    if (ledKey == ledKeys[i]) {
      return ledColorKeys[i];
    }
  }
  return 0; //probably not ideal, but a start
}

//////////////////////////  get led color by index //////////////////////////

int enoLEDmapper::getLEDColByIdx(int  ledIdx) {
  return ledColorKeys[ledIdx];
}

//////////////////////////  get led idx by name //////////////////////////

int enoLEDmapper::getLEDIdxByName(char *ledName, bool caseSensitive) {

  int cmp;
  for (int i=0; i<numLEDkeysUsed; i++) {
    if (caseSensitive) {cmp = strcmp(    ledName, ledNames[i]);}
    else               {cmp = strcasecmp(ledName, ledNames[i]);}

    if (cmp==0) {return i;}
  }
  return -1; 
}

//////////////////////////  get led idx by key //////////////////////////

int enoLEDmapper::getLEDIdxByKey(char ledKey) {
  for (int i=0; i<numLEDkeysUsed; i++) {
    if (ledKey == ledKeys[i]) {return i;}
  }
  return -1;
}
    
////////////////////////// set led by name //////////////////////////

int enoLEDmapper::setLEDByName(char *ledName, char ledColor, int ledBrightness, bool caseSensitive) {
  int ledIdx = getLEDIdxByName(ledName, caseSensitive);
  setLedByIdx(ledIdx, ledColor, ledBrightness);
}

////////////////////////// set led by key //////////////////////////

int enoLEDmapper::setLEDByKey(char ledKey, char ledColor, int ledBrightness) {
  int ledIdx = getLEDIdxByKey(ledKey);
  setLedByIdx(ledIdx, ledColor, ledBrightness);
}

////////////////////////// set led by idx //////////////////////////

int enoLEDmapper::setLEDByIdx(int ledIdx, char ledColor, int ledBrightness) {
}

// end //
