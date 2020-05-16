#pragma once

struct Model {
  unsigned solderingIronTempMax;
  unsigned solderingIronTemp;
  unsigned heatgunTempMax;
  unsigned heatgunTemp;
  unsigned heatgunFanPWM;
};

void initModel(Model& model);

