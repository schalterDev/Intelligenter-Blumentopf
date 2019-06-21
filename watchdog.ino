#include <avr/wdt.h>
#include <avr/power.h>
#include <avr/sleep.h>

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
  WDTCSR = _BV(WDP3) | _BV(WDP0) | _BV(WDIE);

  // enable interrupt
  WDTCSR |= _BV(WDIE);
  sei();

  enterSleepMode = true;
}

void enterSleep() {
  debugMessage("Enter sleep mode");
  debugMessage("----------------");

  digitalWrite(MOISTURE_VCC_PIN, LOW);
  
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
  sleep_enable();  
  power_adc_disable();    // disable analog inputs
  power_spi_disable();
  power_timer0_disable();
  power_timer2_disable();
  power_twi_disable();
  sleep_mode();
  // Program resumes after this line when the WDT Interrupt is finished
  debugMessage("woke up");
  sleep_disable();
  power_all_enable();
}

ISR(WDT_vect) {
  wdtCounter++;
  debugMessage("Watchdog interrupt start, counter: ");
  debugMessage(wdtCounter);
  
  enterSleepMode = true;
}

void switchInterrupt() {
  enterManualMode = true;
}

