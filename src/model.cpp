#include "model.hpp"
#include <Arduino.h>

void initModel(Model &model) {
  // later on read this values from EEPROM
  model.solderingIronTempMax = 180;
  model.heatgunTempMax = 250;
  model.solderingIronTemp = 0;
  model.heatgunTemp = 0;
  model.heatgunFanPWM = 0;
}
