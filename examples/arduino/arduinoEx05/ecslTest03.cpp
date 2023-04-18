// Progressive examples, toward PyGame Zero Xi (Extended Interaction) integration
// Brygg Ullmer, Clemson University
// Support by NSF CNS-1828611
// Begun 2023-04

#include "SerialCommands.h"
#include <stdio.h>
#include <stdlib.h>
#include "enoStrLightmapper.h"
#include "enoColormapper.h"
#include <unistd.h>

////////////////// led & serial code /////////////////////

char serial_command_buffer[32];
Stream *SerialProxy = new Stream();
SerialCommands serCmds(SerialProxy, serial_command_buffer, sizeof(serial_command_buffer), "\r\n", " ");

void lightBlue(SerialCommands *sender) {printf("blue\n");}
void lightRed( SerialCommands *sender) {printf("red\n");}
void lightOff( SerialCommands *sender) {printf("off\n");}
void unrecognized(SerialCommands* sender, const char* cmd) {lightOff(sender);}

SerialCommand cmd_red( "r", lightRed,  true);
SerialCommand cmd_blue("b", lightBlue, true);
SerialCommand cmd_off( "-", lightOff,  true);

////////////////// main /////////////////////

int main() {
  enoStrLightmapper ecsl = enoStrLightmapper(5);
  enoColormapper ecm = enoColormapper();

  serCmds.SetDefaultHandler(unrecognized);
  serCmds.AddCommand(&cmd_red);
  serCmds.AddCommand(&cmd_blue);  

  char *ecmHelp = ecm.getColorSummaryStr();
  printf("\ncolormap summary\n");
  printf(  "----------------\n");
  printf("%s", ecmHelp);

  ecsl.setLightByIdx(0, 'r', 10);
  ecsl.showLight();

  printf("\nlightmap summary\n");
  printf(  "----------------\n");
  char *ecslHelp = ecsl.getLightSummaryStr();
  printf("%s", ecslHelp);
  //free(ecslHelp); //curious; when done, next call segfaults

  ecsl.setLightByIdx(1, 'b', 20);
  ecslHelp = ecsl.getLightSummaryStr();
  printf("%s", ecslHelp);

  while (1) {
    serCmds.ReadSerial();
    sleep(.2);
  }
}

/// end ///
