
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <UniversalTelegramBot.h>

#include <LM35.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C  lcd(0x3F,2,1,0,4,5,6,7);
#include <RTClib.h>
#include "RTClib.h" 
RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"}; //prosedur pembacaan I2C

File myFile;
int sensorPin = A0; 
int sensorValue;
float DSoil; 
 
void setup()
{

Serial.begin(9600);
lcd.begin (16,2); // for 16 x 2 LCD module
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    rtc.adjust(DateTime(2019, 5, 22, 15, 26, 37));
  };
  lcd.setCursor(0,0);
  lcd.print("Data Logger");
  lcd.setCursor(0,1); 
  lcd.print("Fakhry");
  delay(1000);
  lcd.clear();
 
 Serial.println("Read MicoSd Card");
 delay(1000);
 if (!SD.begin(4)) 
 {
 Serial.println("Failed read microsd card on module!");
  lcd.setCursor(0,0);
  lcd.print("Failed read microsd");
  lcd.clear();
 return;
 }
 Serial.println("Success read microsd card");
 lcd.setCursor(0,0);
  lcd.print("Success read microsd");
 delay(1000);
 lcd.clear();
}


void rtcTime(){
DateTime now = rtc.now();
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    lcd.setCursor(0,1);
    lcd.print(now.year(), DEC);
    lcd.print('/');
    lcd.print(now.month(), DEC);
    lcd.print('/');
    lcd.print(now.day(), DEC);
    //lcd.print(" (");
    //lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
    lcd.print(" ");
    lcd.print(now.hour(), DEC);
    lcd.print(':');
    lcd.print(now.minute(), DEC);
    //lcd.print(':');
    //lcd.print(now.second(), DEC); 
  
}


void Soil(){
  sensorValue = analogRead(sensorPin); 
  int nilaiADC = analogRead(sensorPin);
  DSoil = ( 100 - ( (nilaiADC/1023.00) * 100 ) );
  Serial.println("Analog Value : ");
    Serial.println(sensorValue);
    Serial.println("Kelebaan Value : ");
      Serial.println(DSoil);
  lcd.setCursor(0,0);
    lcd.print(sensorValue);
    lcd.print(" Soil:");
    lcd.print(DSoil);
  };
  
void loop(){
  rtcTime();
  Soil();
  DateTime now = rtc.now();
 myFile = SD.open("Soil.CSV", FILE_WRITE); //Membuka File datalogger.txt
 if (myFile) // jika file tersedia tulis data
 {myFile.print(now.day(), DEC);
      myFile.print('/');
      myFile.print(now.month(), DEC);
      myFile.print('/');
      myFile.print(now.year(), DEC);
      myFile.print(" , ");
      myFile.print(now.hour(), DEC);
      myFile.print(':');
      myFile.print(now.minute(), DEC);
      myFile.print(':');
      myFile.print(now.second(), DEC);
      myFile.print(" , ");
      myFile.print("Soil");
      myFile.print(" , ");
      myFile.println(DSoil);

  myFile.close();
    Serial.println("done.");
      lcd.setCursor(15,0);
      lcd.print("Y");
 }
 else 
 {
 Serial.println("Failed open datalogger.txt"); // jika gagal print error
 lcd.setCursor(15,0);
 lcd.print("N");
 }
delay(5000);//total jeda yaitu 5 detik karena proses penulisan data kurang lebih 3 detik
lcd.clear();
}
