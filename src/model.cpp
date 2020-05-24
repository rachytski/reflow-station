#include "model.hpp"

void initModel(Model &model) {
  // later on read this values from EEPROM
  model.solderingIronTempMax.set(180);
  model.heatgunTempMax.set(250);
  model.solderingIronTemp.set(0);
  model.heatgunTemp.set(0);
  model.heatgunFanPWM.set(0);
  model.mode.set(-1);
}
