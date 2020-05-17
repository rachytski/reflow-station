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
  updateController(model);  
  updateView(viewModel);
}
