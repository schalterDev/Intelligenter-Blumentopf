#include <avr/wdt.h>
#include <avr/power.h>
#include <avr/sleep.h>

volatile int wdtCounter = 0;

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
  WDTCSR |= 1<<WDIE;
  sei();

  enterSleepMode = true;
}

void enterSleep() {
  #ifdef DEBUG
    Serial.println("Enter sleep mode");
    delay(100);
  #endif
  
  set_sleep_mode(SLEEP_MODE_PWR_SAVE);  
  sleep_enable();  
  power_adc_disable();    // disable analog inputs
  power_spi_disable();
  power_timer0_disable();
  power_timer2_disable();
  power_twi_disable();
  sleep_mode();
  // Program resumes after this line when the WDT Interrupt iss finished
  #ifdef DEBUG
    Serial.println("woke up");
  #endif
  sleep_disable();
  power_all_enable();     // Komponenten wieder aktivieren
}

ISR(WDT_vect) {  
  #ifdef DEBUG
    wdtCounter++;
    Serial.print("Watchdog interrupt start, counter: ");
    Serial.println(wdtCounter);
  #endif
  
  enterSleepMode = true;
}
