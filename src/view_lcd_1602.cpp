#include <Arduino.h>
#include <LiquidCrystal.h>

#include "view_lcd_1602.hpp"
#include "view_model.hpp"
#include "pinout.hpp"

LiquidCrystal lcd(12,11,10,9,8,7);

unsigned viewUpdateTicks = 0;
unsigned viewUpdateCycles = 200;

void initView(ViewModel& viewModel) {
  // ui-related code
  pinMode(SW_PIN, INPUT_PULLUP);
  pinMode(DT_PIN, INPUT_PULLUP);
  pinMode(CLK_PIN, INPUT_PULLUP);

  Serial.begin(9600);
  
  lcd.begin(16, 2);

  updateView(viewModel);
}

void updateView(ViewModel &viewModel) {
//  if (viewUpdateTicks++ % viewUpdateCycles) {
//    return;
//  }

//  viewUpdateTicks %= viewUpdateCycles;

  char buf[32];
  
  char ironSep = viewModel.buttonPos == 0 ? '*' : '-';
  char heatGunSep = viewModel.buttonPos == 1 ? '*' : '-';
  char fanSep = viewModel.buttonPos == 2 ? '*' : '=';
  
  sprintf(buf,
          "S=%3d%c%3d",
          viewModel.solderingIronTemp,
          ironSep,
          viewModel.solderingIronTempMax);
  buf[31] = 0;
  
  lcd.setCursor(0, 0);
  lcd.write(buf);
  Serial.println(buf);
  
  sprintf(buf,
          "H=%3d%c%3d F%c%3d",
          viewModel.heatgunTemp,
          heatGunSep,
          viewModel.heatgunTempMax,
          fanSep,
          viewModel.heatgunFanPWM);
  buf[31] = 0;

  lcd.setCursor(0, 1);
  lcd.write(buf);
  Serial.println(buf);
}
