#include <LiquidCrystal.h>

// digital pins
#define HEATING_GUN_COOLING_FAN 2
#define SOLDERING_IRON_HEATING_ELEMENT 3
#define HEATING_GUN_HEATING_ELEMENT 4
// analogue pins
#define HEATING_GUN_TEMP_SENSOR0 3
#define SOLDERING_IRON_TEMP_SENSOR0 4

LiquidCrystal lcd(10,9,8,7,6,5);

void setup() {
  //initialize pins
  pinMode(HEATING_GUN_COOLING_FAN, OUTPUT);
  pinMode(HEATING_GUN_HEATING_ELEMENT, OUTPUT);
  pinMode(SOLDERING_IRON_HEATING_ELEMENT, OUTPUT);

  // initial state
  digitalWrite(HEATING_GUN_COOLING_FAN, HIGH);
  digitalWrite(HEATING_GUN_HEATING_ELEMENT, LOW);
  digitalWrite(SOLDERING_IRON_HEATING_ELEMENT, LOW);

  lcd.begin(16, 2);
  
  Serial.begin(9600);
}

void loop() {
  lcd.setCursor(0, 1);
  lcd.print("there, there...");
  
  const int solderingIronTempMax = 180;
  const int heatGunTempMax = 250;
  
  int solderingIronTemp = analogRead(SOLDERING_IRON_TEMP_SENSOR0);
  int heatGunTemp = analogRead(HEATING_GUN_TEMP_SENSOR0);

  bool shouldHeatSolderingIron = solderingIronTemp < solderingIronTempMax;
  bool shouldHeatHeatGun = heatGunTemp < heatGunTempMax;

  digitalWrite(HEATING_GUN_COOLING_FAN, HIGH);
  digitalWrite(HEATING_GUN_HEATING_ELEMENT, shouldHeatHeatGun ? HIGH : LOW);
  digitalWrite(SOLDERING_IRON_HEATING_ELEMENT, shouldHeatSolderingIron ? HIGH : LOW);

  // diagnostics output
  char buf[1024];
  sprintf(buf, "Iron: %d, Gun: %d", solderingIronTemp, heatGunTemp);
  Serial.println(buf);
}
