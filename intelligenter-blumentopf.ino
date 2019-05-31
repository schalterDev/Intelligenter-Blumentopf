#include <avr/wdt.h>

#include "pins.h"

// add a comment for production
#define DEBUG

volatile bool firstManualMode = true;
volatile bool enterSleepMode = false;
volatile bool enterManualMode = false;

void startPump() {
  #ifdef DEBUG
    Serial.println("Start Pump");
  #endif
  
  digitalWrite(PUMP_PIN, HIGH);
  delay(DUARTION_PUMP);
  digitalWrite(PUMP_PIN, LOW);

  #ifdef DEBUG
    Serial.println("Stop Pump");
  #endif
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
  if (enterManualMode && firstManualMode) {
    firstManualMode = false;
    enterManualMode = false;
  }
  
  if (enterManualMode) {
    #ifdef DEBUG
      Serial.println("manual mode");
    #endif
    
    startPump();
  
    enterManualMode = false;
  }
  
  if (enterSleepMode) {
    if (needWater()) {
      #ifdef DEBUG
        Serial.println("Needs water");
      #endif
      startPump();
    }

    if (enoughWater()) {
      digitalWrite(WATER_FUEL_DIOD_PIN, LOW);
    } else {
      digitalWrite(WATER_FUEL_DIOD_PIN, HIGH);
    }
    
    enterSleepMode = false;
  }

  if (!enterSleepMode && !enterManualMode) {
    enterSleep();
  }
}
