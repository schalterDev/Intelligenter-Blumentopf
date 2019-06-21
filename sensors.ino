/**
 * @returns a value between 0 and 1023
 */
int readAnalog(int pin, char string) {
  int value = analogRead(pin);
  debugMessage("read pin ", false);
  intDebugMessage(pin, false);
  debugMessage(string, false);
  intDebugMessage(value, true);
  return value;
}

int readPotentiomenter() {
  return readAnalog(POT_PIN, 'p');
}

int readMoistureSensor() {  
  return readAnalog(MOISTURE_PIN, 'm');
}

bool enoughWater() {
  bool needWater = digitalRead(WATER_FUEL_MEASURE_PIN) == LOW;

  debugMessage("Enough water: ", false);
  intDebugMessage(needWater, true);
  return needWater;
}

bool needWater() {
  digitalWrite(MOISTURE_VCC_PIN, HIGH);
  delay(10);
  
  int potentiometer = readPotentiomenter();
  int moistureSensor = readMoistureSensor();

  #ifdef KAPAZITIVE_MOISUTRE_SENSOR
    return kapazitiveSensorNeedWater(moistureSensor, potentiometer);
  #else
    return resitiveSensorNeedWater(moistureSensor, potentiometer);
  #endif
}

bool kapazitiveSensorNeedWater(int moistureSensor, int potentiometer) {
  debugMessage("Use kapazitive moisture sensor", true);

  int potentiometerValueMapRange = map(potentiometer, 0, 1023, KAPAZITIVE_WATER_VALUE, KAPAZITIVE_AIR_VALUE);
  
  debugMessage("Mapped potentiometer: ", false);
  intDebugMessage(potentiometerValueMapRange, true);
    
  return moistureSensor > potentiometerValueMapRange;
}

bool resitiveSensorNeedWater(int moistureSensor, int potentiometer) {
  debugMessage("Use resitive moisture sensor", true);

  int potentiometerValueMapRange = map(potentiometer, 0, 1023, RESITIVE_WATER_VALUE, RESITIVE_AIR_VALUE);

  debugMessage("Mapped potentiometer: ", false);
  intDebugMessage(potentiometerValueMapRange, true);
 
  return moistureSensor > potentiometerValueMapRange;
}

