#include <avr/wdt.h>

#include "pins.h"

// add a comment for production
#define DEBUG

volatile bool enterSleepMode = false;

void setup() {
  #ifdef DEBUG
    Serial.begin(9600);
    Serial.println("Started");
   #endif
  
  setupPins();
  
  setupWatchdog();
}

void loop() {
  if (enterSleepMode) {
    if (needWater()) {
      #ifdef DEBUG
        Serial.println("Needs water");
      #endif
    }
    
    enterSleepMode = false;
    enterSleep();
  }
}
