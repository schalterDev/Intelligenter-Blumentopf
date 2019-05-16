
#include <avr/wdt.h>

int const POT_PIN = A0;

/**
 * Starts the watchdog with 8s 
 * After this the main loop will stop and only external interrupts will work
 * ISR(WDT_vect) is called after 8 seconds
 */
void setupWatchdog() {
  cli();

  // Reset watchdog
  MCUSR &= ~_BV(WDRF);
  
  // Start the WDT and start change sequence.
  WDTCSR |= _BV(WDCE) | _BV(WDE);
  // Configure the prescaler and the WDT for interrupt mode only
  // 8s: WDP3 & WDP0
  // 1s: WDP2 & WDP1
  WDTCSR =  _BV(WDP2) | _BV(WDP1) | _BV(WDIE);
  sei();
}

/**
 * @returns a value between 0 and 1023
 */
int readPotentiomenter() {
  return analogRead(POT_PIN);
}

void setup() {
  // Potentiometer
  pinMode(POT_PIN, INPUT);

  Serial.begin(9600);
  Serial.println("Started");
  
  setupWatchdog();
}

void loop() {}

ISR(WDT_vect) {
  Serial.println("Watchdog interrupt start");

  int potentiometerValue = readPotentiomenter();
   
  Serial.print("Potentiometer: ");
  Serial.println(potentiometerValue);
  Serial.println("Watchdog interrupt end");
}
