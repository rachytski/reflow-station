#include "controller.hpp"

#include <Arduino.h>

#include "pinout.hpp"
#include "model.hpp"

void updateInput(Model &model) {
}

void initController(Model& model) {
  pinMode(HEATING_GUN_COOLING_FAN, OUTPUT);
  pinMode(HEATING_GUN_HEATING_ELEMENT, OUTPUT);
  pinMode(SOLDERING_IRON_HEATING_ELEMENT, OUTPUT);

  pinMode(HEATING_GUN_TEMP_SENSOR0, INPUT);
  pinMode(SOLDERING_IRON_TEMP_SENSOR0, INPUT);

  model.solderingIronTemp.set(analogRead(SOLDERING_IRON_TEMP_SENSOR0));
  model.heatgunTemp.set(analogRead(HEATING_GUN_TEMP_SENSOR0));
  model.heatgunFanPWM.set(255);
}

void updateController(Model& model) {
  updateInput(model);
  
  // TODO: implement PID controller for both iron and heatgun

  model.solderingIronTemp.set(analogRead(SOLDERING_IRON_TEMP_SENSOR0));
  model.heatgunTemp.set(analogRead(HEATING_GUN_TEMP_SENSOR0));

  bool shouldHeatSolderingIron = model.solderingIronTemp.get() < model.solderingIronTempMax.get();
  bool shouldHeatHeatGun = model.heatgunTemp.get() < model.heatgunTempMax.get();

  analogWrite(HEATING_GUN_COOLING_FAN, model.heatgunFanPWM.get());
  digitalWrite(HEATING_GUN_HEATING_ELEMENT, shouldHeatHeatGun ? HIGH : LOW);
  digitalWrite(SOLDERING_IRON_HEATING_ELEMENT, shouldHeatSolderingIron ? HIGH : LOW);
}
