// Progressive examples, toward PyGame Zero Xi (Extended Interaction) integration
// Brygg Ullmer, Clemson University
// Support by NSF CNS-1828611
// Begun 2023-04

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "enoStrLightmapper.h"
#include "enoColormapper.h"
#include "SerialCommands.h"

////////////////// led & serial code /////////////////////

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
