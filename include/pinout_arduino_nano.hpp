#pragma once

// physical pinout for the Arduino Nano

// control pins
#define HEATING_GUN_COOLING_FAN 3
#define SOLDERING_IRON_HEATING_ELEMENT 2
#define HEATING_GUN_HEATING_ELEMENT 4

// rotary encoder pins
#define SW_PIN 6
#define DT_PIN 5
#define CLK_PIN 13

// analogue pins for thermal sensors
#define HEATING_GUN_TEMP_SENSOR0 A3
#define SOLDERING_IRON_TEMP_SENSOR0 A4
