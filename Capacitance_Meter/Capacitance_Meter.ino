#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C  lcd(0x3F,2,1,0,4,5,6,7);

int charge = 8;
int discharge = 9;
int analogPin = A0;
unsigned long start_timer=0;
unsigned long stop_timer=0;
unsigned long duration=0;
////////////////////////////////
float voltage=3;
float answer=0.0;
int measure (void);
/////////////////////////////////
void setup() 
{
  lcd.begin (16,2); // for 16 x 2 LCD module
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
Serial.begin(9600);
lcd.begin(16, 2);
lcd.print("RANGE 1uF-4700uF");
lcd.setCursor(0,1);
lcd.print("place capacitor ");
pinMode(discharge,INPUT);
pinMode(charge,OUTPUT);
digitalWrite(charge,HIGH);
}
//1021 1022 1023
void loop() 
{
 
 while(measure()>=1010 && measure()<=1030)
 {
   lcd.setCursor(0,1);
    lcd.print("place capacitor ");
    delay(200);
    lcd.setCursor(0,1);
    lcd.print("                ");  
    delay(200);
 }
 delay(2000);
 lcd.setCursor(0,1);
 lcd.print("                ");
  while(1)
  {
    //////////////////////////////////////////////discharging
    pinMode(charge,INPUT);
    pinMode(discharge,OUTPUT);
    digitalWrite(discharge,LOW);
    lcd.setCursor(0,1);
    lcd.print("Discharging-");//12
    while(voltage>2.0)
    {
    voltage=measure();
    delay(100);
    lcd.setCursor(12,1);
    answer=voltage * (99.0 / 1023.0);
    lcd.print((99-answer),0);
    lcd.setCursor(14,1);
    lcd.print("%");
    }
    
    lcd.setCursor(0,1);
    lcd.print("                ");
    delay(1000);
    lcd.setCursor(0,1);
    lcd.print("charging-");//9
    lcd.setCursor(13,1);
    lcd.print("%");
  
    //////////////////////////////////////////////charging 
    pinMode(discharge,INPUT);
    pinMode(charge,OUTPUT);
    digitalWrite(charge,HIGH);
    start_timer=micros();
    
    while(measure()<648)
    {
      lcd.setCursor(9,1);
      lcd.print(measure()*(100.0/1023.0),1);
    }
    
    stop_timer=micros();
    duration=stop_timer-start_timer;
    answer=duration/10000;
    lcd.clear();
   // lcd.setCursor(0,1);
   // lcd.print("                ");
    lcd.setCursor(0,0);
    lcd.print("value = ");
    lcd.print(answer);
    lcd.print("uF"); 
    delay(3000);
    while(1)
    {
    lcd.setCursor(0,1);
    lcd.print("reset to measure");
    delay(200);
     lcd.setCursor(0,1);
    lcd.print("                ");  
    delay(200);
    }
   
}
}

int measure (void)
{
  int value;
  value=analogRead(analogPin);
  return value;
}
