
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <UniversalTelegramBot.h>

#include <LM35.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
File myFile;
int sensorPin = A0; 
int sensorValue;
float DSoil; 
 
void setup()
{

Serial.begin(9600);
 
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
    
  
}


void Soil(){
  sensorValue = analogRead(sensorPin); 
  int nilaiADC = analogRead(sensorPin);
  DSoil = ( 100 - ( (nilaiADC/1023.00) * 100 ) );
  Serial.println("Analog Value : ");
    Serial.println(sensorValue);
    Serial.println("Kelebaan Value : ");
      Serial.println(DSoil);
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
 }
 else 
 {
 Serial.println("Failed open datalogger.txt"); // jika gagal print error
 }
delay(5000);//total jeda yaitu 5 detik karena proses penulisan data kurang lebih 3 detik
lcd.clear();
}
