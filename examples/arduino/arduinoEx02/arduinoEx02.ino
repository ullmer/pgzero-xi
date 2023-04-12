// Progressive examples, toward PyGame Zero Xi (Extended Interaction) integration
// Brygg Ullmer, Clemson University
// Support by NSF CNS-1828611
// Begun 2023-04

// https://learn.adafruit.com/adafruit-grand-central/adapting-sketches-to-m0
#if defined(ARDUINO_SAMD_ZERO) && defined(SERIAL_PORT_USBVIRTUAL)
  // Required for Serial on Zero based boards
  #define Serial SERIAL_PORT_USBVIRTUAL
#endif

#define LED0 13

int millisPerUpdate = 1000; //how many milliseconds should pass before each ~heartbeat update
int millisLastUpdate = 0;
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

////////////////// serialCount /////////////////////

int serialIdx = 0;

void serialCount() {
  Serial.println(serialIdx); serialIdx += 1;
}

////////////////// toggle LED0 /////////////////////

int led0State = 0;
void toggleLED0() {
  if (led0State == 0) {digitalWrite(LED0, HIGH); led0State=1;}
  else               {digitalWrite(LED0, LOW);  led0State=0;}
}

////////////////// heartbeat /////////////////////
void heartbeat() {
  toggleLED0(); serialCount();
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