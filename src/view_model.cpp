#include "view_model.hpp"
#include <Arduino.h>
#include "model.hpp"

void initViewModel(ViewModel &viewModel, Model &model) {
  model.solderingIronTempMax.connect(&viewModel.solderingIronTempMax, true);
  model.heatgunTempMax.connect(&viewModel.heatgunTempMax, true);
  model.heatgunFanPWM.connect(&viewModel.heatgunFanPWM, true);
  model.solderingIronTemp.connect(&viewModel.solderingIronTemp);
  model.heatgunTemp.connect(&viewModel.heatgunTemp);
  
  // maybe read some ui state from the EEPROM, like buttonPos e.t.c
  viewModel.buttonPos = 0;
}
