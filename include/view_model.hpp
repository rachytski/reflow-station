#pragma once

#include "property.hpp"

struct ViewModel {
  property<unsigned> solderingIronTempMax;
  ro_property<unsigned> solderingIronTemp;
  property<unsigned> heatgunTempMax;
  ro_property<unsigned> heatgunTemp;
  property<unsigned> heatgunFanPWM;
  property<int> mode;
};

struct Model;

void initViewModel(ViewModel &viewModel, Model &model);

