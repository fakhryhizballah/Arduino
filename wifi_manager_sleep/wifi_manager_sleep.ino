#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <WiFiManager.h>    
#include <SoftwareSerial.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
WiFiUDP ntpUDP;
const long utcOffsetInSeconds = 0;
NTPClient timeClient(ntpUDP,"id.pool.ntp.org",25200);
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

int Led_OnBoard = 2;

void setup() {
    Serial.begin(115200);
  WiFiManager wifiManager;
  //panggilan balik saat menyambung ke jaringan, yaitu saat bekerja dalam mode stasiun  wifiManager.setSaveConfigCallback(saveConfigCallback); 
  wifiManager.autoConnect("TMP-999", "12345678");
  Serial.println("connected...yeey :)");
  Serial.println("Connecting");
  digitalWrite(Led_OnBoard, HIGH);
  timeClient.begin();
  timeClient.update();
  Serial.println(timeClient.getFormattedTime());
  }


void loop() {
 
  delay(1000);
  Serial.print(daysOfTheWeek[timeClient.getDay()]);
  Serial.print(", ");
  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());
  ESP.deepSleep(30e6); 
  }
