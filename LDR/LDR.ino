#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C  lcd(0x20,2,1,0,4,5,6,7); 

const int LDRIn = A0;
int inPin = 4;
int ledPin = 5;
int val = 0;
int inRes = 6;
int rst = 0;


void setup() {
  Serial.begin(9600);
  lcd.begin (16,2); // for 16 x 2 LCD module
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(LOW);
  lcd.setCursor(0,0);
 lcd.print("Turbidity Sensor");
 delay(1000);
 lcd.clear();
 lcd.print("Tekan Tombol");
 pinMode(inPin, INPUT);
 pinMode(ledPin, OUTPUT);
}

void ReadSensor(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Nilai");
  digitalWrite(ledPin, HIGH);
  int sensorValue = analogRead(LDRIn);
  lcd.setCursor(0,1);
  lcd.print(sensorValue);
  delay(2000);
}

void loop() {
  val = digitalRead(inPin);
  if (val == LOW){
    ReadSensor();
  } else {
    digitalWrite(ledPin, LOW);
  }
  rst = digitalRead(inRes);
  if ( rst == LOW){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Tekan Tombol");
  }
}
