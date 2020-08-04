#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include <ESP8266HTTPClient.h>
#include "DHT.h"
#define DHTPIN 13 
#define DHTTYPE DHT22 

int Led_OnBoard = 2;  
DHT dht(DHTPIN, DHTTYPE);

int Sentdata = 0 ;
const int delaydata = 60;

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C  lcd(0x3f, 16,2); 

const char *ssid     = "Azimi";
const char *password = "bismillah";

const long utcOffsetInSeconds = 25200;

char daysOfTheWeek[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumaat", "Sabtu"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "id.pool.ntp.org", utcOffsetInSeconds);

const char *host = "103.253.212.155";

void setup(){
  Serial.begin(115200);
  pinMode(Led_OnBoard, OUTPUT);
  dht.begin();

  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("WiFi Connecting");
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
    digitalWrite(Led_OnBoard, LOW);
    delay(250);
    Serial.print(".");
    digitalWrite(Led_OnBoard, HIGH);
    delay(250);
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
    delay(500); 
    digitalWrite(Led_OnBoard, LOW);
    delay(500);
    digitalWrite(Led_OnBoard, HIGH);
    return;
  }
    // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  lcd.setCursor(0, 1);
  lcd.print(F("H:"));
  lcd.print(h,1);
  lcd.print("% ");
  lcd.print(F("T:"));
  lcd.print(t,1);
  lcd.print(F("C"));
  lcd.println(' ');

  digitalWrite(Led_OnBoard, HIGH);
  
  if (Sentdata <= delaydata)
  {
    delay(1000);
    Sentdata++;
  } else {
     HTTPClient http;    //Declare object of class HTTPClient

  String TempValueSend, HumiValueSend, HeatVauleSend, postData;

  //int ldrvalue=dht.getHumidity(); 
  TempValueSend = String(t);
  HumiValueSend = String(h);
  HeatVauleSend = String(hic);
  
  //postData = "Tvalue=" + TempValueSend + "&Hvalue" + HumiValueSend;
  postData = "Tvalue=" + TempValueSend + "&Hvalue=" + HumiValueSend + "&Hevalue=" + HeatVauleSend;

  
  http.begin("http://dht.spairum.com/insertDB.php");              //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header

  int httpCode = http.POST(postData);   //Send the request
  String payload = http.getString();    //Get the response payload

  Serial.println("Temp Value=" + TempValueSend);
  Serial.println("Humidity Value=" + HumiValueSend);
  Serial.println("Heat index=" +HeatVauleSend); 
  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payloadSS
  
  http.end();
  Sentdata = 0;

  digitalWrite(Led_OnBoard, LOW);
  delay(1000);
  }

}
