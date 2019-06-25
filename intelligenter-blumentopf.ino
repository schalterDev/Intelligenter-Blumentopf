#include "pins.h"
#include "debug.h"

volatile bool firstManualMode = true;
volatile bool enterSleepMode = false;
volatile bool enterManualMode = false;
volatile unsigned long wdtCounter = 0;
volatile unsigned long lastwdtCounter = 0;

void startPump() {
  debugMessage("Start Pump");
  
  digitalWrite(PUMP_PIN, HIGH);
  delay(DURATION_PUMP);
  digitalWrite(PUMP_PIN, LOW);

  debugMessage("Stop Pump");
}

void setup() {
  #ifdef DEBUG
    Serial.begin(38400);
  #endif
   
  debugMessage("Started");
  
  setupPins();
  initBluetooth();
  
  startCalibrate();
  setupWatchdog();  
}

void loop() {    
  if (enterManualMode && firstManualMode) {
    firstManualMode = false;
    enterManualMode = false;
  }
  
  if (enterManualMode && lastwdtCounter != wdtCounter) {
    debugMessage("manual mode");
    startPump();
    enterManualMode = false;

    lastwdtCounter = wdtCounter;
  } else if (enterManualMode) {
    enterManualMode = false;
  }
  
  if (enterSleepMode) {    
    if (USE_TIME_INTERVAL) {
      unsigned long timeInterval = readPotentiometerTime();
      debugMessage("Mapped time interval in seconds divided by 8: ", false);
      debugMessageL(timeInterval);
    
      debugMessage("wdt counter: ", false);
      debugMessageL(wdtCounter);
      if (wdtCounter >= timeInterval) {
        debugMessage("Needs water (Interval)");
        wdtCounter = 0;
        startPump();
        lastwdtCounter = wdtCounter;
      }
    } else if (needWater()) {
      debugMessage("Needs water");
      startPump();
      lastwdtCounter = wdtCounter;
    }
    
    enterSleepMode = false;
  }

  if (enoughWater()) {
      digitalWrite(WATER_FUEL_DIOD_PIN, LOW);
    } else {
      digitalWrite(WATER_FUEL_DIOD_PIN, HIGH);
    }

  if (!enterSleepMode && !enterManualMode) {
    enterSleep();
  }
}
