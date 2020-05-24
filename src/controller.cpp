#include "controller.hpp"

#include <Arduino.h>

#include "pinout.hpp"
#include "model.hpp"

template <typename T> T clamp(T const&val, T const &min, T const &max) {
  T t = val;
  if (t < min) {
    t = min;
  }
  if (t > max) {
    t = max;
  }
  return t;
}

void updateInput(Model &model) {
  int swButtonState = digitalRead(SW_PIN);

  if (swButtonState == LOW && (swButtonState != model.swButtonState)) {
    model.mode.set((model.mode.get() + 2) % 4 - 1);
  }

  int dirMultiplier = 0;
  
  int clkButtonState = digitalRead(CLK_PIN);
  int dtButtonState = digitalRead(DT_PIN);
  if (clkButtonState != model.clkButtonState) {
    dirMultiplier = dtButtonState != clkButtonState ? 1 : -1;
  }

  if (model.mode.get() == 0) {
    int newVal = model.solderingIronTempMax.get() + dirMultiplier * 10;
    model.solderingIronTempMax.set(clamp(newVal, 0, 600));
  }

  if (model.mode.get() == 1) {
    int newVal = model.heatgunTempMax.get() + dirMultiplier * 10;
    model.heatgunTempMax.set(clamp(newVal, 0, 700));
  }

  if (model.mode.get() == 2) {
    int newVal = model.heatgunFanPWM.get() + dirMultiplier * 10;    
    model.heatgunFanPWM.set(clamp(newVal, 0, 255));
  }

  model.swButtonState = swButtonState;
  model.dtButtonState = dtButtonState;
  model.clkButtonState = clkButtonState;
}

void initController(Model& model) {
  pinMode(SW_PIN, INPUT_PULLUP);
  pinMode(DT_PIN, INPUT_PULLUP);
  pinMode(CLK_PIN, INPUT_PULLUP);
  
  pinMode(HEATING_GUN_COOLING_FAN, OUTPUT);
  pinMode(HEATING_GUN_HEATING_ELEMENT, OUTPUT);
  pinMode(SOLDERING_IRON_HEATING_ELEMENT, OUTPUT);

  pinMode(HEATING_GUN_TEMP_SENSOR0, INPUT);
  pinMode(SOLDERING_IRON_TEMP_SENSOR0, INPUT);

  model.solderingIronTemp.set(analogRead(SOLDERING_IRON_TEMP_SENSOR0));
  model.heatgunTemp.set(analogRead(HEATING_GUN_TEMP_SENSOR0));
  model.heatgunFanPWM.set(255);
}

unsigned compensateSolderingIronThermalTransfer(int solderingIronTempRaw) {
  // linear fit of the following {from, to} measurements:
  // {150, 90}, {200, 120}, {250, 160}, {300, 180}, {350, 220}, {400, 260},
  // {450, 280}, {500, 310}
  return unsigned(clamp(int(0.638095 * solderingIronTempRaw - 4.88095), 0, 1000));
}

unsigned compensateHeatgunTemp(int heatgunTempRaw) {
  return heatgunTempRaw;
}

void updateController(Model& model) {
  updateInput(model);
  
  // TODO: implement PID controller for both iron and heatgun

  model.solderingIronTemp.set(compensateSolderingIronThermalTransfer(analogRead(SOLDERING_IRON_TEMP_SENSOR0)));
  model.heatgunTemp.set(compensateHeatgunTemp(analogRead(HEATING_GUN_TEMP_SENSOR0)));

  bool shouldHeatSolderingIron = model.solderingIronTemp.get() < model.solderingIronTempMax.get();
  bool shouldHeatHeatGun = model.heatgunTemp.get() < model.heatgunTempMax.get();

  shouldHeatHeatGun &= model.mode.get() == 1;
  shouldHeatSolderingIron &= model.mode.get() == 0;
  
  analogWrite(HEATING_GUN_COOLING_FAN, model.heatgunFanPWM.get());
  digitalWrite(HEATING_GUN_HEATING_ELEMENT, shouldHeatHeatGun ? HIGH : LOW);
  digitalWrite(SOLDERING_IRON_HEATING_ELEMENT, shouldHeatSolderingIron ? HIGH : LOW);
}
  
