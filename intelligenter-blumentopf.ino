#include "pins.h"

volatile bool firstManualMode = true;
volatile bool enterSleepMode = false;
volatile bool enterManualMode = false;
volatile unsigned long wdtCounter = 0;

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
  
  if (enterManualMode) {
    debugMessage("manual mode");
    
    startPump();
  
    enterManualMode = false;
  }
  
  if (enterSleepMode) {
    unsigned long timeInterval = map(readPotentiomenter(), 0, 1023, 2, 151200L);
    
    debugMessage("Mapped time interval in seconds divided by 8: ");
    debugMessage(timeInterval);
    
    if (USE_TIME_INTERVAL && wdtCounter >= timeInterval) {
      debugMessage("Needs water (Interval)");
      wdtCounter = 0;
      startPump();
    } else if (needWater()) {
      debugMessage("Needs water");
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

void debugMessage(char message[]) {
  #ifdef DEBUG
    Serial.println(message);
  #endif

  #ifdef DEBUG_BLUETOOTH
    sendDataByBluetooth(message);
  #endif
}

void intDebugMessage(int message) {
  #ifdef DEBUG
    Serial.println(message);
  #endif

  #ifdef DEBUG_BLUETOOTH
    sendIntByBluetooth(message);
  #endif
}

