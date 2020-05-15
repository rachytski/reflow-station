#include <LiquidCrystal.h>

#include "lcd_1602_ui.hpp"
#include "state.hpp"

LiquidCrystal lcd(12,11,10,9,8,7);

void setupUI() {
  lcd.begin(16, 2);
}

void reportState(State const &state) {
  // diagnostics output
  char buf[1024];
  sprintf(buf, "Iron: %d, Gun: %d", state.solderingIronTemp, state.heatGunTemp);
  lcd.setCursor(0, 0);
  lcd.print(buf);
//  Serial.println(buf);
}
