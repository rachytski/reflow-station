#include <Arduino.h>
#include "state.hpp"
#include "lcd_1602_ui.hpp"

// digital pins
#define HEATING_GUN_COOLING_FAN 2
#define SOLDERING_IRON_HEATING_ELEMENT 3
#define HEATING_GUN_HEATING_ELEMENT 4
// analogue pins
#define HEATING_GUN_TEMP_SENSOR0 3
#define SOLDERING_IRON_TEMP_SENSOR0 4

void setup() {
  //initialize pins
  pinMode(HEATING_GUN_COOLING_FAN, OUTPUT);
  pinMode(HEATING_GUN_HEATING_ELEMENT, OUTPUT);
  pinMode(SOLDERING_IRON_HEATING_ELEMENT, OUTPUT);

  // initial state
  digitalWrite(HEATING_GUN_COOLING_FAN, HIGH);
  digitalWrite(HEATING_GUN_HEATING_ELEMENT, LOW);
  digitalWrite(SOLDERING_IRON_HEATING_ELEMENT, LOW);

  setupUI();
  
  Serial.begin(9600);
}

State state;

void loop() {
  state.solderingIronTempMax = 180;
  state.heatGunTempMax = 250;
  
  state.solderingIronTemp = analogRead(SOLDERING_IRON_TEMP_SENSOR0);
  state.heatGunTemp = analogRead(HEATING_GUN_TEMP_SENSOR0);
  
  bool shouldHeatSolderingIron = state.solderingIronTemp < state.solderingIronTempMax;
  bool shouldHeatHeatGun = state.heatGunTemp < state.heatGunTempMax;

  digitalWrite(HEATING_GUN_COOLING_FAN, HIGH);
  digitalWrite(HEATING_GUN_HEATING_ELEMENT, shouldHeatHeatGun ? HIGH : LOW);
  digitalWrite(SOLDERING_IRON_HEATING_ELEMENT, shouldHeatSolderingIron ? HIGH : LOW);

  int sw = digitalRead(6);
  int dt = digitalRead(5);
  int clk = digitalRead(13);

  reportState(state);
  
//  sprintf(buf, "SW:%d,DT:%d,CLK:%d", sw, dt, clk);
//  lcd.setCursor(0, 1);
//  lcd.print(buf);
//  Serial.println(buf);
}
