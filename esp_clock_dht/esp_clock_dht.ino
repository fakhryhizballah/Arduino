#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include <ESP8266HTTPClient.h>
#include "DHT.h"
#define DHTPIN 13 
#define DHTTYPE DHT22 
int Led_OnBoard = 2;  
DHT dht(DHTPIN, DHTTYPE);

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C  lcd(0x3f, 16,2); 

const char *ssid     = "Azimi";
const char *password = "bismillah";

const long utcOffsetInSeconds = 25200;

char daysOfTheWeek[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumaat", "Sabtu"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "id.pool.ntp.org", utcOffsetInSeconds);

void setup(){
  Serial.begin(115200);
  dht.begin();

  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("WiFi Connecting");

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
    

    lcd.print(".");
  }
  timeClient.begin();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("IP address: ");
  lcd.setCursor(0,1);
  lcd.println(WiFi.localIP());
  lcd.println(' ');
  delay(3000);
  lcd.clear();
}

void loop() {
  timeClient.update();
  lcd.setCursor(0, 0);
  lcd.print(daysOfTheWeek[timeClient.getDay()]);
  lcd.print(", ");
  lcd.println(timeClient.getFormattedTime());


  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    delay(200); 
    digitalWrite(Led_OnBoard, LOW);
    delay(200);
    digitalWrite(Led_OnBoard, HIGH);
    return;
  }
    // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  lcd.setCursor(0, 1);
  lcd.print(F("H:"));
  lcd.print(h);
  lcd.print("%");
  lcd.print(F("T:"));
  lcd.print(t);
  lcd.print(F("C"));
  lcd.println(' ');
  delay(1000);
}
