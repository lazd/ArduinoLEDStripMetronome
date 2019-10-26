#include "FastLED.h"
#include <Bounce2.h>

#define LED_PIN       2
#define SWITCH_PIN    3
#define NUM_LEDS      35
#define FADE_FACTOR   15
#define MAX_INTERVAL  3000

// The interval between beats
unsigned long timing = 600; // 100 bpm by default

unsigned long currentTime;
unsigned int currentLED = 0;
unsigned long lastButtonPressTime = 0;
unsigned long lastLEDUpdateTime = 0;

// The direction of movement along the LED strip
boolean direction = true;

Bounce debouncer = Bounce();

CRGBArray<NUM_LEDS> leds;
void setup() {
  debouncer.attach(SWITCH_PIN, INPUT_PULLUP);
  debouncer.interval(20);
  
  pinMode(LED_PIN, OUTPUT);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS); 
}

void loop() {
  currentTime = millis();
  debouncer.update();

  if (debouncer.fell()) {
    unsigned int newTiming = currentTime - lastButtonPressTime;
    if (newTiming <= MAX_INTERVAL) {
      // Update timing to match the interval of button presses
      timing = (newTiming + timing) / 2;
    }

    lastButtonPressTime = currentTime;
  }

  updateLEDs();
}

unsigned long lastTime = currentTime;
void updateLEDs() {
  if (currentTime - lastTime >= timing) {
    // Switch the direction of movement on the beat
    lastTime = currentTime;
    direction = !direction;
  }

  if ((currentTime - lastLEDUpdateTime) >= (timing / NUM_LEDS)) {
    // Ensure we don't go out of bounds while waiting for a direction switch
    if (direction) {
      if (currentLED == NUM_LEDS - 1) {
        currentLED = NUM_LEDS - 1;
      }
      else { 
        currentLED++;
      }
    }
    else {
      if (currentLED == 0) {
        currentLED = 0;
      }
      else {
        currentLED--;      
      }
    }

    leds[currentLED] = CRGB::Red;
    FastLED.show();
  
    // Fade out everything behind and in front of the current LED
    leds(0, currentLED).fadeToBlackBy(FADE_FACTOR);
    leds(currentLED, NUM_LEDS - 1).fadeToBlackBy(FADE_FACTOR);

    lastLEDUpdateTime = currentTime;
  }
}
