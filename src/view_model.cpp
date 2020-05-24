#include "view_model.hpp"
#include <Arduino.h>
#include "model.hpp"

void initViewModel(ViewModel &viewModel, Model &model) {
  model.solderingIronTempMax.connect(&viewModel.solderingIronTempMax);
  model.heatgunTempMax.connect(&viewModel.heatgunTempMax);
  model.heatgunFanPWM.connect(&viewModel.heatgunFanPWM);
  model.solderingIronTemp.connect(&viewModel.solderingIronTemp);
  model.heatgunTemp.connect(&viewModel.heatgunTemp);
  model.mode.connect_bi(&viewModel.mode);
}
