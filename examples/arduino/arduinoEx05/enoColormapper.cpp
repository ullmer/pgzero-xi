// Enodia colormapper
// Brygg Ullmer, Clemson University
// Partial support from NSF CNS-1828611
// Begun 2023-04
// LLGPL3

#include <stdio.h>
#include <cstring>
#include "enoColormapper.h"

////////////////////////// constructor //////////////////////////

enoColormapper::enoColormapper(int maxColorkeysPerChunk, bool generateStandardColors) {
  allocateBuffers(maxColorkeysPerChunk);
  nextColormapperChunk = NULL;
  if (generateStandardColors) {populateStandardColors();}
}

////////////////////////// populate standard colors //////////////////////////

void enoColormapper::populateStandardColors() {
  registerColor('r', "red",    0xff0000);
  registerColor('g', "green",  0x00ff00);
  registerColor('b', "blue",   0x0000ff);
  registerColor('w', "white",  0xffffff);
  registerColor('o', "orange", 0xff8000);
  registerColor('p', "purple", 0x800080);
}

////////////////////////// allocate buffers //////////////////////////

void enoColormapper::allocateBuffers(int numColorkeys) {
  maxColorkeysPerChunk = numColorkeys;
  colorKeys  = new  char[numColorkeys];
  colorNames = new char*[numColorkeys];
  colorVals  = new   int[numColorkeys];
  numColorkeysUsed = 0;
}

//////////////////////////  register color //////////////////////////

void enoColormapper::registerColor(char colorKey, char colorName[], int colorVal) {
  if (numColorkeysUsed >= maxColorkeysPerChunk) {return;} // need to handle better

  colorKeys[numColorkeysUsed]  = colorKey;
  colorNames[numColorkeysUsed] = colorName;
  colorVals[numColorkeysUsed]  = colorVal;
  numColorkeysUsed++;
}


//////////////////////////  getColorSummaryStr //////////////////////////

char *enoColormapper::getColorSummaryStr() {
  int resultlen = 0;
  char **buffer = new char*[numColorkeysUsed];
  char colorNameBuffer[maxColorNameLen];
  char *currentColor, *currentLine;

  for (int i=0; i<numColorkeysUsed; i++) {
    currentLine  = new char[maxCharsPerLine];

    currentColor = colorNames[i];
    if (strlen(currentColor) > maxColorNameLen) { // avoid buffer overflow error
      currentColor = strncpy(colorNameBuffer, colorNames[i], maxColorNameLen);
    }
    
    sprintf(currentLine, "%2i %c %6X %15s\n", i, colorKeys[i], colorVals[i], currentColor); //could be refined further
    resultlen += strlen(currentLine);
    buffer[i] = currentLine;
  }

  char *result = new char[resultlen];

  int currentCharIdx = 0;
  for (int i=0; i<numColorkeysUsed; i++) {
    currentLine = buffer[i];
    strncpy(&result[currentCharIdx], currentLine, maxCharsPerLine);
    currentCharIdx += strlen(currentLine);
  }

  return result;
}

//////////////////////////  get color by key //////////////////////////

int  enoColormapper::getColorByKey(char colorKey) {
  for (int i=0; i<numColorkeysUsed; i++) {
    if (colorKey == colorKeys[i]) {
      return colorVals[i];
    }
  }
  return 0; //probably not ideal, but a start
}

//////////////////////////  get color by key //////////////////////////

int   enoColormapper::getColorByIdx(int  colorIdx) {
  return colorVals[colorIdx];
}

//////////////////////////  get color by key //////////////////////////

int   enoColormapper::getColorByName(char *colorName, bool caseSensitive) {

  int cmp;
  for (int i=0; i<numColorkeysUsed; i++) {
    if (caseSensitive) {cmp = strcmp( colorName, colorNames[i]);}
    else               {cmp = strcmpi(colorName, colorNames[i]);}

    if (cmp==0) {return colorVals[i];}
  }
  return 0; //probably not ideal, but a start
}
    
// end //
