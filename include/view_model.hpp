#pragma once

#include "property.hpp"

struct ViewModel {
  property<unsigned> solderingIronTempMax;
  property<unsigned> solderingIronTemp;
  property<unsigned> heatgunTempMax;
  property<unsigned> heatgunTemp;
  property<unsigned> heatgunFanPWM;
  unsigned buttonPos;
};

struct Model;

void initViewModel(ViewModel &viewModel, Model &model);

