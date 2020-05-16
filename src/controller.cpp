#include "controller.hpp"

#include <Arduino.h>

#include "pinout.hpp"
#include "model.hpp"

void initController(Model& model) {
  pinMode(HEATING_GUN_COOLING_FAN, OUTPUT);
  pinMode(HEATING_GUN_HEATING_ELEMENT, OUTPUT);
  pinMode(SOLDERING_IRON_HEATING_ELEMENT, OUTPUT);

  pinMode(HEATING_GUN_TEMP_SENSOR0, INPUT);
  pinMode(SOLDERING_IRON_TEMP_SENSOR0, INPUT);

  model.solderingIronTemp = analogRead(SOLDERING_IRON_TEMP_SENSOR0);
  model.heatgunTemp = analogRead(HEATING_GUN_TEMP_SENSOR0);
  model.heatgunFanPWM = 255;
}

void updateController(Model& model) {
  // TODO: implement PID controller for both iron and heatgun

  model.solderingIronTemp = analogRead(SOLDERING_IRON_TEMP_SENSOR0);
  model.heatgunTemp = analogRead(HEATING_GUN_TEMP_SENSOR0);
  model.heatgunFanPWM -= 1;
    
  digitalWrite(HEATING_GUN_COOLING_FAN, model.heatgunFanPWM);
  digitalWrite(HEATING_GUN_HEATING_ELEMENT, (model.heatgunTemp < model.heatgunTempMax) ? HIGH : LOW);
  digitalWrite(SOLDERING_IRON_HEATING_ELEMENT, (model.solderingIronTemp < model.solderingIronTempMax) ? HIGH : LOW);
}
