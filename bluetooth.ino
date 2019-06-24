#include <SoftwareSerial.h>

SoftwareSerial bluetooth(BLUETOOTH_TX_PIN, BLUETOOTH_RX_PIN);
  
const static int BLUETOOTH_SPEED = 9600;
const char NO_DATA = -1;

void initBluetooth() {
  bluetooth.begin(BLUETOOTH_SPEED);
  bluetooth.println("bluetooth available");
}

void sendDataByBluetooth(String string, bool newLine) {
  if (newLine)
    bluetooth.println(string);
  else
    bluetooth.print(string);
}

void sendDataByBluetooth(int message, bool newLine) {
   if (newLine)
    bluetooth.println(message);
  else
    bluetooth.print(message);
}

void sendDataByBluetooth(unsigned long message, bool newLine) {
  if (newLine)
    bluetooth.println(message);
  else
    bluetooth.print(message);
}

//char readByteByBluetooth() {
//  char dataBluetooth = NO_DATA;
//  
//  if (bluetooth.available() > 0) {
//    dataBluetooth = bluetooth.read();
//    debugMessage("bluetooth: ", false);
//    debugMessage(dataBluetooth);
//  }
//
//  return dataBluetooth;
//}
