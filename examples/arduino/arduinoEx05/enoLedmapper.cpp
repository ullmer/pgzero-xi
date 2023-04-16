// Enodia ledmapper
// Brygg Ullmer, Clemson University
// Partial support from NSF CNS-1828611
// Begun 2023-04
// LLGPL3

#include <stdio.h>
#include <cstring>
#include "enoLEDmapper.h"

////////////////////////// constructor //////////////////////////

enoLEDmapper::enoLEDmapper(int maxLEDkeysPerChunk) {
  allocateBuffers(maxLEDkeysPerChunk);
  nextLEDmapperChunk = NULL;
  if (generateStandardLEDs) {populateStandardLEDs();}
}

////////////////////////// populate standard leds //////////////////////////

void enoLEDmapper::populateStandardLEDs() {
  registerLED('r', "red",    0xff0000);
  registerLED('g', "green",  0x00ff00);
  registerLED('b', "blue",   0x0000ff);
  registerLED('w', "white",  0xffffff);
  registerLED('o', "orange", 0xff8000);
  registerLED('p', "purple", 0x800080);
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

void enoLEDmapper::registerLED(char ledKey, const char ledName[], int ledVal) {
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
