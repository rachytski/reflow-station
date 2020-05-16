#include <Arduino.h>
#include "view_model.hpp"
#include "controller.hpp"
#include "model.hpp"
#include "view.hpp"
#include "pinout.hpp"

Model model;
ViewModel viewModel;

void setup() {
  initModel(model);
  initController(model);
  initViewModel(viewModel, model);
  initView(viewModel);
}

void loop() {
  updateView(viewModel);
  updateController(model);

  // wiring models manually, such updates should be automated 
  viewModel.solderingIronTemp = model.solderingIronTemp;
  viewModel.heatgunTemp = model.heatgunTemp;
  model.solderingIronTempMax = viewModel.solderingIronTempMax;
  model.heatgunTempMax = viewModel.heatgunTempMax;
  model.heatgunFanPWM = viewModel.heatgunFanPWM;
}
