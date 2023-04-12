// Progressive examples, toward PyGame Zero Xi (Extended Interaction) integration
// Brygg Ullmer, Clemson University
// Support by NSF CNS-1828611
// Begun 2023-04

// https://learn.adafruit.com/adafruit-grand-central/adapting-sketches-to-m0
#if defined(ARDUINO_SAMD_ZERO) && defined(SERIAL_PORT_USBVIRTUAL)
  // Required for Serial on Zero based boards
  #define Serial SERIAL_PORT_USBVIRTUAL
#endif

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

int serialIdx = 0;

void serialCount() {
  Serial.println(serialIdx); serialIdx += 1;
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  serialCount();
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
}