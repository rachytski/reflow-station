#pragma once

#include <Arduino.h>

#include "property.hpp"

struct Model {
  property<unsigned> solderingIronTempMax;
  property<unsigned> solderingIronTemp;
  property<unsigned> heatgunTempMax;
  property<unsigned> heatgunTemp;
  property<unsigned> heatgunFanPWM;
  property<int> mode;
  int swButtonState = HIGH;
  int dtButtonState = HIGH;
  int clkButtonState = HIGH;
};

void initModel(Model& model);

