#include <FastLED.h>
#define LED_PIN     7
#define NUM_LEDS    22

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS); 
}

void loop() {
  //light up LEDs for 3 seconds
  for(int i = 0; i<NUM_LEDS; i++){
    leds[i] = CRGB(50,50,50);
  }
  FastLED.show();
  delay(3000);

  //turn off LEDs for 3 seconds
  for(int i = 0; i<NUM_LEDS; i++){
    leds[i] = CRGB(0,0,0);
  }
  FastLED.show();
  delay(3000);
}
