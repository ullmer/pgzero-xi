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
  nextColormapperChunk = 0;
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
  colorVals  = new   int[numColorkeys];
  colorNames = new const char*[numColorkeys];
  numColorkeysUsed = 0;
}

//////////////////////////  register color //////////////////////////

void enoColormapper::registerColor(char colorKey, const char colorName[], int colorVal) {
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
  char *currentLine;
  char *currentColor;

  for (int i=0; i<numColorkeysUsed; i++) {
    currentLine  = new char[maxCharsPerLine];
    int colorNameLen = strlen(colorNames[i]);

    if (colorNameLen > maxColorNameLen) { // avoid buffer overflow error
      currentColor = strncpy(colorNameBuffer, colorNames[i], maxColorNameLen);
    } else {
      currentColor = strcpy(colorNameBuffer, colorNames[i]);
    }
    
    sprintf(currentLine, "%2i %c %6X %s\n", i, colorKeys[i], colorVals[i], currentColor); //could be refined further
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

//////////////////////////  getColorYamlStr //////////////////////////

char *enoColormapper::getColorYamlStr() {
  int resultlen = 0;
  char **buffer = new char*[numColorkeysUsed];
  char colorNameBuffer[maxColorNameLen];
  char *currentLine;
  char *currentColor;

  int maxColorNameLen=0;
  for (int i=0; i<numColorkeysUsed; i++) {
    int len = strlen(colorNames[i]);
    if (len>maxColorNameLen) {maxColorNameLen = len;}
  }

  char *namePad = new char[maxColorNameLen];
  for (int i=0; i<maxColorNameLen; i++) {namePad[i]=' ';} // toward alignment

  for (int i=0; i<numColorkeysUsed; i++) {
    currentLine  = new char[maxCharsPerLine];
    int colorNameLen = strlen(colorNames[i]);

    if (colorNameLen > maxColorNameLen) { // avoid buffer overflow error
      currentColor = strncpy(colorNameBuffer, colorNames[i], maxColorNameLen);
    } else {
      currentColor = strcpy(colorNameBuffer, colorNames[i]);
    }
    
    //sprintf(currentLine, "%2i: {key=%c, val=0x%06X, name=%s}\n", 
    //    i, colorKeys[i], colorVals[i], currentColor);

    int  namePadOffset = colorNameLen;
    char *namePad2 = &namePad[namePadOffset];

    sprintf(currentLine, "%s: %s{key=%c, val=0x%06X}\n", 
            currentColor, namePad2, colorKeys[i], colorVals[i]);

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
    if (caseSensitive) {cmp = strcmp(    colorName, colorNames[i]);}
    else               {cmp = strcasecmp(colorName, colorNames[i]);}

    if (cmp==0) {return colorVals[i];}
  }
  return 0; //probably not ideal, but a start
}
    
// end //
