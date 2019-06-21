#include <SoftwareSerial.h>

SoftwareSerial bluetooth(BLUETOOTH_TX_PIN, BLUETOOTH_RX_PIN);
  
const static int BLUETOOTH_SPEED = 9600;
const int NO_DATA = 250;

void initBluetooth() {
  bluetooth.begin(BLUETOOTH_SPEED);
  bluetooth.println("bluetooth available");
}

/*
int readByteByBluetooth() {
  int dataBluetooth = NO_DATA;
  
  if (bluetooth.available()) {
    dataBluetooth = bluetooth.read();
  }

  return dataBluetooth;
}
*/

void sendDataByBluetooth(char string[], bool newLine) {
  if (newLine)
    bluetooth.println(string);
  else
    bluetooth.print(string);
}

void sendIntByBluetooth(int message, bool newLine) {
   if (newLine)
    bluetooth.println(message);
  else
    bluetooth.print(message);
}

