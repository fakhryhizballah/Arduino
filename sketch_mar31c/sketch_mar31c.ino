#include <LiquidCrystal_I2C.h>
#include <LCD.h>
#include <Wire.h>

LiquidCrystal_I2C  lcd(0x3f ,2,1,0,4,5,6,7);

void setup() {

Serial.begin(115200);

//Use predefined PINS consts

Wire.begin(D2, D1);

lcd.begin(16,2);

lcd.home();

lcd.print("Hello, NodeMCU");

}

void loop() {
  }
