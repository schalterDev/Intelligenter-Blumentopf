/**
 * @returns a value between 0 and 1023
 */
int readAnalog(int pin, char string) {
  #ifdef DEBUG
    int value = analogRead(pin);
    Serial.print("read pin ");
    Serial.print(pin);
    Serial.print(", ");
    Serial.print(string);
    Serial.print(": ");
    Serial.println(value);
    return value;
  #endif
  
  return analogRead(pin);
}

int readPotentiomenter() {
  return readAnalog(POT_PIN, 'p');
}

int readMoistureSensor() {  
  return readAnalog(MOISTURE_PIN, 'm');
}

bool enoughWater() {
  bool needWater = digitalRead(WATER_FUEL_MEASURE_PIN) == LOW;

  #ifdef DEBUG
    Serial.print("Enough water: ");
    Serial.println(needWater);
  #endif
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
  #ifdef DEBUG
    Serial.println("Use kapazitive moisture sensor");
  #endif

  int potentiometerValueMapRange = map(potentiometer, 0, 1023, KAPAZITIVE_WATER_VALUE, KAPAZITIVE_AIR_VALUE);

  #ifdef DEBUG
    Serial.print("Mapped potentiometer: ");
    Serial.println(potentiometerValueMapRange);
  #endif
    
  return moistureSensor > potentiometerValueMapRange;
}

bool resitiveSensorNeedWater(int moistureSensor, int potentiometer) {
  #ifdef DEBUG
    Serial.println("Use resitive moisture sensor");
  #endif

  int potentiometerValueMapRange = map(potentiometer, 0, 1023, RESITIVE_WATER_VALUE, RESITIVE_AIR_VALUE);

  #ifdef DEBUG
    Serial.print("Mapped potentiometer: ");
    Serial.println(potentiometerValueMapRange);
  #endif
  
  return moistureSensor > potentiometerValueMapRange;
}

