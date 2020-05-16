#include "view_model.hpp"
#include <Arduino.h>
#include "model.hpp"

void initViewModel(ViewModel &viewModel, Model const &model) {
  // maybe read some ui state from the EEPROM, like buttonPos e.t.c
  viewModel.solderingIronTempMax = model.solderingIronTempMax;
  viewModel.heatgunTempMax = model.heatgunTempMax;
  viewModel.heatgunFanPWM = model.heatgunFanPWM;
  viewModel.solderingIronTemp = model.solderingIronTemp;
  viewModel.heatgunTemp = model.heatgunTemp;
  viewModel.buttonPos = 0;
}
