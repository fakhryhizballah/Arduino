#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <DNSServer.h>
#include <WiFiManager.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LCD.h>
#include <Arduino_JSON.h>

const char *host = "http://api.openweathermap.org/data/2.5/onecall?lat=-0.0333&lon=109.3333&exclude=hourly,daily&appid=d09d65ed123bb55a3a6fc0d22eb73c22";


const int dry = 595; // value for dry sensor
const int wet = 239; // value for wet sensor


#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C  lcd(0x3F,2,1,0,4,5,6,7); 
int Led_OnBoard = 2;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  lcd.begin (16,2); // for 16 x 2 LCD module
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("Loading");
  delay(500);
   lcd.print(" .");
  delay(500);
     lcd.print(" .");
  delay(500);
     lcd.print(" .");
  delay(500);
  lcd.setCursor(0,2);
  lcd.print("Menunggu Wifi");
  pinMode(Led_OnBoard, OUTPUT);
  Serial.begin(115200);
  WiFiManager wifiManager;
  wifiManager.autoConnect("Nama Wifi", "12345678");
  lcd.setCursor(0,1);
  lcd.print("Wifi Tersambung");
  lcd.print(' ');
  Serial.println("connected...yeey :)");
  Serial.println("Connecting");
  digitalWrite(Led_OnBoard, HIGH);
  delay(2000);
  lcd.clear();
  
     
      int h = 0;
      int uv = 0;
      
}

void loop() {
  int sensorVal = analogRead(A0);

  // Sensor has a range of 239 to 595
  // We want to translate this to a scale or 0% to 100%
  // More info: https://www.arduino.cc/reference/en/language/functions/math/map/
  int percentageHumididy = map(sensorVal, wet, dry, 100, 0); 

  Serial.print(percentageHumididy);
  Serial.println("%");
  
  HTTPClient http;
  http.begin(host);
  int httpCode = http.GET();
  Serial.println(httpCode);
//  Serial.println(http.getString());
   if (httpCode > 0) 
    {
//      StaticJsonDocument<200> doc;
//      deserializeJson(doc, http.getString());
      JSONVar myObject = JSON.parse(http.getString());
//      const char* Temp = doc["current"]["feels_like"];
      Serial.println(myObject["current"]["uvi"]);
      int k = 0;
      int temp = 0;
      int h = 0;
      int uv = 0;
      k = myObject["current"]["feels_like"];
      temp = k -273.15;
      uv = (myObject["current"]["uvi"]);
      h = (myObject["current"]["humidity"]);
      lcd.setCursor(0,0);
  lcd.print("Soil:");
  lcd.print(percentageHumididy);
  lcd.print("% ");
  lcd.print("H:");
  lcd.print(h);
  lcd.print("%");
  lcd.print(' ');
  
  lcd.setCursor(0,2);
  lcd.print("T:");
  lcd.print(temp);
  lcd.print("C ");
  lcd.print("UV:");
  lcd.print(uv);
    }
  http.end(); //Close connection
  
    
      lcd.print(' ');
  delay(3000);

  

}
