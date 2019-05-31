void setupPins() {
  pinMode(POT_PIN, INPUT);
  pinMode(MOISTURE_PIN, INPUT);
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(WATER_FUEL_MEASURE_PIN, INPUT);
  pinMode(WATER_FUEL_DIOD_PIN, OUTPUT);
  
  pinMode(SWITCH_PIN, INPUT);
  digitalWrite(SWITCH_PIN, HIGH);
  attachInterrupt(digitalPinToInterrupt(SWITCH_PIN), switchInterrupt, RISING);
}
