#pragma once

struct ViewModel {
  unsigned solderingIronTempMax;
  unsigned solderingIronTemp;
  unsigned heatgunTempMax;
  unsigned heatgunTemp;
  unsigned heatgunFanPWM;
  unsigned buttonPos;
};

struct Model;

void initViewModel(ViewModel &viewModel, Model const &model);

