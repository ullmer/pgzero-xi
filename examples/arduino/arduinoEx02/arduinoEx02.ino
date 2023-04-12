// Progressive examples, toward PyGame Zero Xi (Extended Interaction) integration
// Brygg Ullmer, Clemson University
// Support by NSF CNS-1828611
// Begun 2023-04

#define LED0 13
//#define BAUD 9600
#define BAUD 115200
#define LED_BRIGHTNESS 1
int millisPerUpdate = 1000; //how many milliseconds should pass before each ~heartbeat update

#include <Adafruit_NeoPixel.h>

#define NUMPIXELS 1
Adafruit_NeoPixel pixels(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

// https://learn.adafruit.com/adafruit-grand-central/adapting-sketches-to-m0
#if defined(ARDUINO_SAMD_ZERO) && defined(SERIAL_PORT_USBVIRTUAL)
  // Required for Serial on Zero based boards
  #define Serial SERIAL_PORT_USBVIRTUAL
#endif



int millisLastUpdate = 0;
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

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.setBrightness(LED_BRIGHTNESS); // not so bright
}

////////////////// serialCount /////////////////////

int serialIdx = 0;

void serialCount() {
  Serial.println(serialIdx); serialIdx += 1;
}

////////////////// toggle LED0 /////////////////////

int led0Activated = 0;
int led1Activated = 1;
int led0State = 0;
int led1State = 0;
void toggleLED() {
  if (led0Activated && led0State == 0) {digitalWrite(LED0, HIGH); led0State=1;}
  else               {digitalWrite(LED0, LOW);  led0State=0;}

  if (led1Activated && led1State == 0) {
    pixels.fill(0xFF0000);
    pixels.show(); led1State=1;
  } else {
    pixels.fill(0x0000FF);
    pixels.show(); led1State=0;
  }
}

////////////////// heartbeat /////////////////////
void heartbeat() {
  toggleLED(); serialCount();
}

////////////////// serial read update /////////////////////
void serialReadUpdate() {
  char ch = Serial.read();
  Serial.print(">>");
  Serial.println(ch); 
}

// the loop function runs over and over again forever
void loop() {
  int currentTime = millis();
  if (millisLastUpdate == 0 || millisLastUpdate + millisPerUpdate < currentTime) {
      heartbeat(); millisLastUpdate = currentTime;
  }
  if (Serial.available()) {serialReadUpdate();}
}