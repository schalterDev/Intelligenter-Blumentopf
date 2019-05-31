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

    if (enoughWater()) {
      Serial.println("LOW");
      digitalWrite(WATER_FUEL_DIOD_PIN, LOW);
    } else {
      Serial.println("HIGH");
      digitalWrite(WATER_FUEL_DIOD_PIN, HIGH);
    }
    
    enterSleepMode = false;
  }

  if (!enterSleepMode) {
    enterSleep();
  }
}
