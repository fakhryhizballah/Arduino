#include "DHT.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

;

#define DHT11_PIN 2

void setup(){
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop()
{
  int chk = DHT.read11(DHT11_PIN);
  lcd.setCursor(0,0); 
  Serial.print("Temp: ");
  Serial.print(DHT.temperature);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0,1);
  Serial.print("Humidity: ");
  Serial.print(DHT.humidity);
  lcd.print("%");
  delay(1000);
}
