void debugMessage(String message, bool newLine = true) {
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

void debugMessage(int message, bool newLine = true) {
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

void debugMessageL(unsigned long message, bool newLine = true) {
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

