// When the arduino starts it is first in calibrate mode
// The user now can adjust the potentiometer to get the right
// treshold for the moisture sensor
// The LED lights when the pump would start 
// by pressing the button the calibrate mode ends and the led blinks 5 times
void startCalibrate() {
  debugMessage("Start Calibrating");
  
  // while the button is not pressed
  while (digitalRead(SWITCH_PIN) == HIGH) {
    if (needWater()) {
      digitalWrite(WATER_FUEL_DIOD_PIN, HIGH);
    } else {
      digitalWrite(WATER_FUEL_DIOD_PIN, LOW);
    }
  }
  
  debugMessage("Calibrated");
  
  for (int i = 0; i < 5; i++) {
    digitalWrite(WATER_FUEL_DIOD_PIN, HIGH);
    delay(200);
    digitalWrite(WATER_FUEL_DIOD_PIN, LOW);
    delay(200);
  }

  if (digitalRead(SWITCH_PIN) == LOW) {
    USE_TIME_INTERVAL = 1;
    debugMessage("activate time interval");
    delay(2000);
  }
}


