#include "pins.h"

volatile bool firstManualMode = true;
volatile bool enterSleepMode = false;
volatile bool enterManualMode = false;
volatile unsigned long wdtCounter = 0;

void startPump() {
  debugMessage("Start Pump", true);
  
  digitalWrite(PUMP_PIN, HIGH);
  delay(DURATION_PUMP);
  digitalWrite(PUMP_PIN, LOW);

  debugMessage("Stop Pump", true);
}

void setup() {
  #ifdef DEBUG
    Serial.begin(38400);
  #endif
   
  debugMessage("Started", true);
  
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
  
  if (enterManualMode) {
    debugMessage("manual mode", true);
    
    startPump();
  
    enterManualMode = false;
  }
  
  if (enterSleepMode) {
    unsigned long timeInterval = map(readPotentiomenter(), 0, 1023, 2, 151200L);
    
    debugMessage("Mapped time interval in seconds divided by 8: ", false);
    debugMessage(timeInterval, true);
    
    if (USE_TIME_INTERVAL && wdtCounter >= timeInterval) {
      debugMessage("Needs water (Interval)", true);
      wdtCounter = 0;
      startPump();
    } else if (needWater()) {
      debugMessage("Needs water", true);
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

void debugMessage(char message[], bool newLine) {
  #ifdef DEBUG
    if (newLine) 
      Serial.println(message);
    else
      Serial.print(message);
  #endif

  #ifdef DEBUG_BLUETOOTH
    sendDataByBluetooth(message, newLine);
  #endif
}

void intDebugMessage(int message, bool newLine) {
  #ifdef DEBUG
    Serial.println(message);
  #endif

  #ifdef DEBUG_BLUETOOTH
    sendIntByBluetooth(message, newLine);
  #endif
}

