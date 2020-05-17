#pragma once

#include "property.hpp"

struct Model {
  property<unsigned> solderingIronTempMax;
  property<unsigned> solderingIronTemp;
  property<unsigned> heatgunTempMax;
  property<unsigned> heatgunTemp;
  property<unsigned> heatgunFanPWM;
};

void initModel(Model& model);

