// Progressive examples, toward PyGame Zero Xi (Extended Interaction) integration
// Brygg Ullmer, Clemson University
// Support by NSF CNS-1828611
// Begun 2023-04

#define LED0 13

#ifndef ARDUINO
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "enoStrLightmapper.h"
#include <SerialCommands.h>
#endif

#ifdef ARDUINO
#include "enoLedmapper.h"
#include "SerialCommands.h"
#endif

#include "enoColormapper.h"

////////////////// led & serial code /////////////////////

#define NUMPIXELS 1
Adafruit_NeoPixel pixels(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

////////////////// setup /////////////////////

void setup() {
  pinMode(13, OUTPUT); // initialize digital pin 13 as an output.
  
  #if defined(NEOPIXEL_POWER)
  pinMode(NEOPIXEL_POWER, OUTPUT);
  digitalWrite(NEOPIXEL_POWER, HIGH);
  #endif

  Serial.begin(9600);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.setBrightness(7); // not so bright
}

////////////////// loop/////////////////////

void loop() {
}

///end///
// Progressive examples, toward PyGame Zero Xi (Extended Interaction) integration
// Brygg Ullmer, Clemson University
// Support by NSF CNS-1828611
// Begun 2023-04


char serial_command_buffer[32];
Stream *SerialProxy = new Stream();
SerialCommands serCmds(SerialProxy, serial_command_buffer, sizeof(serial_command_buffer), "\r\n", " ");

int cursorIdx = 0;
enoStrLightmapper *ecsl;

/////// purple /////// 

void lightPurple(SerialCommands *sender) {
  ecsl->setLightByIdx(cursorIdx++, 'p', 20);

  #ifndef ARDUINO
  printf("purple\n");
  char *ecslHelp = ecsl->getLightSummaryStrCompact();
  printf("%s\n", ecslHelp); free(ecslHelp); 
  #endif 
}

/////// orange /////// 

void lightOrange( SerialCommands *sender) {
  ecsl->setLightByIdx(cursorIdx++, 'o', 20);

  #ifndef ARDUINO
  printf("orange\n");
  char *ecslHelp = ecsl->getLightSummaryStrCompact();
  printf("%s\n", ecslHelp); free(ecslHelp); 
  #endif
}

void lightOff( SerialCommands *sender) {printf("off\n");}
void unrecognized(SerialCommands* sender, const char* cmd) {lightOff(sender);}

SerialCommand cmd_orange("o", lightOrange,  true);
SerialCommand cmd_purple("p", lightPurple, true);
SerialCommand cmd_off(   "-", lightOff,  true);

////////////////// main /////////////////////

int main() {
  ecsl = new enoStrLightmapper(5);
  enoColormapper ecm = enoColormapper();

  serCmds.SetDefaultHandler(unrecognized);
  serCmds.AddCommand(&cmd_orange);
  serCmds.AddCommand(&cmd_purple);  

  while (1) {
    serCmds.ReadSerial();
    sleep(.2);
  }
}

/// end ///
