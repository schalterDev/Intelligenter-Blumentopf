/**
 * @returns a value between 0 and 1023
 */
int readAnalog(int pin, String string) {
  int value = analogRead(pin);
  debugMessage("read pin ", false);
  debugMessage(pin, false);
  debugMessage(", ", false);
  debugMessage(string, false);
  debugMessage(": ", false);
  debugMessage(value);
  return value;
}

int readPotentiomenter() {
  return readAnalog(POT_PIN, "potentiometer");
}

int readMoistureSensor() {  
  return readAnalog(MOISTURE_PIN, "moisture");
}

unsigned long readPotentiometerTime() {
  int potentiometer = readPotentiomenter();
  if (potentiometer < 2) {
    return 1;
  }
  
  float timeIntervalMap = mapFloat((float) potentiometer, 0.0, 1023.0, 10.8, 17.2); // 2^17.2
  debugMessage("mapped value: ", false);
  debugMessage(timeIntervalMap);
  return (unsigned long) pow(2.0, timeIntervalMap);
}

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

bool enoughWater() {
  bool needWater = digitalRead(WATER_FUEL_MEASURE_PIN) == LOW;

  debugMessage("Enough water: ", false);
  debugMessage(needWater);
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
  debugMessage("Use kapazitive moisture sensor");

  int potentiometerValueMapRange = map(potentiometer, 0, 1023, KAPAZITIVE_WATER_VALUE, KAPAZITIVE_AIR_VALUE);
  
  debugMessage("Mapped potentiometer: ", false);
  debugMessage(potentiometerValueMapRange);
    
  return moistureSensor > potentiometerValueMapRange;
}

bool resitiveSensorNeedWater(int moistureSensor, int potentiometer) {
  debugMessage("Use resitive moisture sensor");

  int potentiometerValueMapRange = map(potentiometer, 0, 1023, RESITIVE_WATER_VALUE, RESITIVE_AIR_VALUE);

  debugMessage("Mapped potentiometer: ", false);
  debugMessage(potentiometerValueMapRange);
 
  return moistureSensor > potentiometerValueMapRange;
}

