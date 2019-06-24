uint8_t const POT_PIN = A0;         // pin 14 in logs
uint8_t const MOISTURE_PIN = A1;    // pin 15 in logs
uint8_t const PUMP_PIN = 8;
uint8_t const WATER_FUEL_MEASURE_PIN = 9;
uint8_t const WATER_FUEL_DIOD_PIN = 4;
uint8_t const SWITCH_PIN = 2;
uint8_t const MOISTURE_VCC_PIN = 12;
uint8_t const BLUETOOTH_TX_PIN = 10;
uint8_t const BLUETOOTH_RX_PIN = 11;

int const DURATION_PUMP = 3000;

// comment when you want to use resisitve sensor (causes erosion)
// #define KAPAZITIVE_MOISUTRE_SENSOR

// value when the sensor is just laying on the table
int const KAPAZITIVE_AIR_VALUE = 830;
// value when the sensor is in water
int const KAPAZITIVE_WATER_VALUE = 420;

int const RESITIVE_AIR_VALUE = 1050;
int const RESITIVE_WATER_VALUE = 250;

// add a comment for production
// #define DEBUG
#define DEBUG_BLUETOOTH

// ignore sensor and use interval to start pump
char USE_TIME_INTERVAL = 0;
// time in seconds divided by 8
unsigned long const TIME_INTERVAL = 2;

