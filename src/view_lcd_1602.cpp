#include <Arduino.h>
#include <LiquidCrystal.h>

#include "view_lcd_1602.hpp"
#include "view_model.hpp"
#include "pinout.hpp"

LiquidCrystal lcd(12,11,10,9,8,13);

unsigned viewUpdateTicks = 0;
unsigned viewUpdateCycles = 100;

void initView(ViewModel& viewModel) {
  lcd.begin(16, 2);

  updateView(viewModel);
}

void updateView(ViewModel &viewModel) {
  if (viewUpdateTicks++ % viewUpdateCycles) {
    return;
  }

  viewUpdateTicks %= viewUpdateCycles;

  char buf[32];
  
  char ironSep = viewModel.mode.get() == 0 ? '*' : '-';
  char heatGunSep = viewModel.mode.get() == 1 ? '*' : '-';
  char fanSep = viewModel.mode.get() == 2 ? '*' : '=';
  
  sprintf(buf,
          "S=%3d%c%3d",
          viewModel.solderingIronTemp.get(),
          ironSep,
          viewModel.solderingIronTempMax.get());
  buf[31] = 0;
  
  lcd.setCursor(0, 0);
  lcd.write(buf);
  
  sprintf(buf,
          "H=%3d%c%3d F%c%3d",
          viewModel.heatgunTemp.get(),
          heatGunSep,
          viewModel.heatgunTempMax.get(),
          fanSep,
          viewModel.heatgunFanPWM.get());
  buf[31] = 0;

  lcd.setCursor(0, 1);
  lcd.write(buf);
}
