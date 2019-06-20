#include <avr/wdt.h>

#include "pins.h"

volatile bool firstManualMode = true;
volatile bool enterSleepMode = false;
volatile bool enterManualMode = false;
volatile unsigned long wdtCounter = 0;

void startPump() {
  #ifdef DEBUG
    Serial.println("Start Pump");
  #endif
  
  digitalWrite(PUMP_PIN, HIGH);
  delay(DURATION_PUMP);
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
  startCalibrate();
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
    long timeInterval = map(readPotentiomenter(), 0, 1023, 2, 151200L);
    #ifdef DEBUG
      Serial.print("Mapped time interval in seconds divided by 8: ");
      Serial.println(timeInterval);
    #endif
    
    if (USE_TIME_INTERVAL && wdtCounter >= timeInterval) {
      #ifdef DEBUG
        Serial.println("Needs water (Interval)");
      #endif
      wdtCounter = 0;
      startPump();
    } else if (needWater()) {
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
