// Progressive examples, toward PyGame Zero Xi (Extended Interaction) integration
// Brygg Ullmer, Clemson University
// Support by NSF CNS-1828611
// Begun 2023-04

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <SerialCommands.h>

////////////////// led & serial code /////////////////////

void lightBlue(SerialCommands *sender) {printf("blue\n");}
void lightRed( SerialCommands *sender) {printf("red\n");}
void lightOff( SerialCommands *sender) {printf("off\n");}
void unrecognized(SerialCommands* sender, const char* cmd) {lightOff(sender);}

char serial_command_buffer[32];

SerialCommands serCmds(serialProxy, serial_command_buffer, sizeof(serial_command_buffer), "\r\n", " ");

SerialCommand cmd_red( "r", lightRed,  true);
SerialCommand cmd_blue("b", lightBlue, true);
SerialCommand cmd_off( "-", lightOff,  true);

int main() {

  serCmds.SetDefaultHandler(unrecognized);
  serCmds.AddCommand(&cmd_red);
  serCmds.AddCommand(&cmd_blue);  

  if (1) {
    serCmds.ReadSerial();
    sleep(.2);
  }
}
/// end ///
