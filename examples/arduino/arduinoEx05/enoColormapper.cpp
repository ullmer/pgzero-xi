// Enodia colormapper
// Brygg Ullmer, Clemson University
// Partial support from NSF CNS-1828611
// Begun 2023-04
// LLGPL3

#include <stdio>
#include "enoColormapper.h"

////////////////////////// constructor //////////////////////////

enoColormapper::enoColormapper(int maxColorkeysPerChunk, generateStandardColors=true) {
  allocateBuffers(maxColorkeysPerChunk);
  nextColormapperChunk = null;
  if (generateStandardColors) {populateStandardColors();}
}

////////////////////////// populate standard colors //////////////////////////

void enoColormapper::populateStandardColors() {
  registerColor('r', 'red',    0xff0000);
  registerColor('g', 'green',  0x00ff00);
  registerColor('b', 'blue',   0x0000ff);
  registerColor('w', 'white',  0xffffff);
  registerColor('o', 'orange', 0xff8000);
  registerColor('p', 'purple', 0x800080);
}

////////////////////////// allocate buffers //////////////////////////

int   enoColormapper::allocateBuffers(int numColorkeys) {
  maxColorkeysPerChunk = numColorkeys;
  colorKeys  = new  char[numColorkeys];
  colorNames = new char*[numColorkeys];
  colorVals  = new   int[numColorkeys];
  numColorkeysUsed = 0;
}

//////////////////////////  register color //////////////////////////

int enoColormapper::registerColor(char colorKey, char *colorName, int colorVal) {
  if (numColorskeysUsed >= maxColorkeysPerChunk) {return;} // need to handle better

  idx = numColorkeysUsed; numColorkeysUsed++;

  colorKeys[idx]  = colorKey;
  colorNames[idx] = colorName;
  colorVals[idx]  = colorVal;
}


//////////////////////////  getColorSummaryStr //////////////////////////

char *enoColormapper::getColorSummaryStr() {
  int resultlen = 0;
  char **buffer = new char*[numColorkeysUsed];
  char colorNameBuffer[maxColorNamelen];
  char *currentColor, *currentLine;

  for (int i=0; i<numColorkeysUsed; i++) {
    currentLine  = new char[maxCharsPerLine];

    currentColor = colorNames[i];
    if strlen(currentColor > maxColornameLen) { // avoid buffer overflow error
      currentColor = strncpy(colorNameBuffer, colorNames[i], maxColornameLen);
    }
    
    sprintf(currentLine, "%c %6X %10s\n", colorKeys[i], colorVals[i], currentColor);
    resultlen += strlen(currentLine);
    buffer[i] = currentLine;
  }

  char *result = new char[resultLen];

  int currentCharIdx = 0;
  for (int i=0; i<numColorkeysUsed; i++) {
    currentLine = buffer[i]
    strncpy(&result[currentCharIdx], currentLine, maxCharsPerLine);
    currentCharIdx += strlen(currentLine)
  }

  return result;
}

//////////////////////////  getColorSummaryStr //////////////////////////

int  enoColormapper::getColorByKey(char colorKey);
int   getColorByIdx(int  colorIdx);
int   getColorByName(char *colorName, bool caseSensitive=false);
    
  private:
    char  *colorKeys;
    char **colorNames;
    int   *colorVals;
    int numColorskeysUsed;
    int maxColorkeysPerChunk;
    enoColormapper *nextColormapperChunk;
}

// end //
