int const POT_PIN = A0;         // pin 14 in logs
int const MOISTURE_PIN = A1;    // pin 15 in logs
int const PUMP_PIN = 10;
int const WATER_FUEL_MEASURE_PIN = 11;
int const WATER_FUEL_DIOD_PIN = 4;
int const SWITCH_PIN = 2;

int const DURATION_PUMP = 3000;

// uncomment when you want to use resisitve sensor (causes erosion)
// #define KAPAZITIVE_MOISUTRE_SENSOR

// value when the sensor is just laying on the table
int const KAPAZITIVE_AIR_VALUE = 830;
// value when the sensor is in water
int const KAPAZITIVE_WATER_VALUE = 420;

int const RESITIVE_AIR_VALUE = 1050;
int const RESITIVE_WATER_VALUE = 250;

// ignore sensor and use interval to start pump
int const USE_TIME_INTERVAL = 1;
// time in seconds divided by 8
int const TIME_INTERVAL = 2;
