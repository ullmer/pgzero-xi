// Progressive examples, toward PyGame Zero Xi (Extended Interaction) integration
// Brygg Ullmer, Clemson University
// Support by NSF CNS-1828611
// Begun 2023-04


#include <SerialCommands.h>


////////////////// led & serial code /////////////////////

void lightBlue(SerialCommands *sender) {printf("blue\n");}
void lightRed( SerialCommands *sender) {printf("red\n");}
void lightOff( SerialCommands *sender) {printf("off\n");}
void unrecognized(SerialCommands* sender, const char* cmd) {lightOff(sender);}

char serial_command_buffer[32];

SerialCommands serCmds(&Serial, serial_command_buffer, sizeof(serial_command_buffer), "\r\n", " ");

SerialCommand cmd_red( "r", lightRed,  true);
SerialCommand cmd_blue("b", lightBlue, true);
SerialCommand cmd_off( "-", lightOff,  true);

////////////////// setup /////////////////////

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  Serial.begin(BAUD);

  #if defined(NEOPIXEL_POWER)
  // If this board has a power control pin, we must set it to output and high
  // in order to enable the NeoPixels. We put this in an #if defined so it can
  // be reused for other boards without compilation errors
  pinMode(NEOPIXEL_POWER, OUTPUT);
  digitalWrite(NEOPIXEL_POWER, HIGH);
  #endif

  pixels.begin();                       // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.setBrightness(LED_BRIGHTNESS); // not so bright

  serCmds.SetDefaultHandler(unrecognized);
  serCmds.AddCommand(&cmd_red);
  serCmds.AddCommand(&cmd_blue);  
}

////////////////// loop /////////////////////

// the loop function runs over and over again forever
void loop() {
  serCmds.ReadSerial();
}
/// end ///
