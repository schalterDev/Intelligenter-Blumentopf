#include <avr/wdt.h>

#include "pins.h"

// add a comment for production
#define DEBUG

volatile bool enterSleepMode = false;

/**
 * @returns a value between 0 and 1023
 */
int readPotentiomenter() {
  return analogRead(POT_PIN);
}

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
    int potentiometerValue = readPotentiomenter();

    #ifdef DEBUG
      Serial.print("Potentiometer: ");
      Serial.println(potentiometerValue);
    #endif
    
    enterSleepMode = false;
    enterSleep();
  }
}
