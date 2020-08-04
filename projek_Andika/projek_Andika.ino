#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>


// Temp DHT
#include "DHT.h"
#define DHTPIN 12 //D5
#define DHTTYPE DHT22
int Led_OnBoard = 2;
DHT dht(DHTPIN, DHTTYPE);

int flowRate;
int y = 5;

// Wifi config


const char *ssid = "Azimi";             // Your wifi Name
const char *password = "alhamdulillah"; // Your wifi Password
const char *host = "103.253.212.155"; //Your pc or server (database) IP, example : 192.168.0.0 , if you are a windows os user, open cmd, then type ipconfig then look at IPv4 Address.

void setup(){
  delay(1000);
  pinMode(Led_OnBoard, OUTPUT);

  Serial.println(F("DHTxx test!"));
  dht.begin();
  
  Serial.begin(115200);
  uart.begin(115200);
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  WiFi.begin(ssid, password);
  Serial.println("Connecting");

  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(Led_OnBoard, LOW);
    delay(250);
    Serial.print(".");
    digitalWrite(Led_OnBoard, HIGH);
    delay(500);
  }
  
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  
  
  }

void loop(){
delay(2000);
flowRate=uart.read();

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

  Serial.print(F("Humidity: % "));
  Serial.print(h);
  Serial.print(F(" Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.print(F("°F"));
  Serial.println(flowRate);

  HTTPClient http; //Declare object of class HTTPClient

  String TempValueSend, HumiValueSend, HeatVauleSend, postData, Debit, LDR, TurbidityVaule;

  //int ldrvalue=dht.getHumidity();
  TempValueSend = String(t);
  HumiValueSend = String(h);
  HeatVauleSend = String(hic);
  Debit = String(flowRate);
  LDR = String(y);
  TurbidityVaule = String(y);
  

  postData = "Tvalue=" + TempValueSend + "&Hvalue=" + HumiValueSend + "&Hevalue=" + HeatVauleSend + "&Flow=" + Debit + "&Ldr=" + LDR + "&Turbidity=" + TurbidityVaule;

  http.begin("http://dht.spairum.com/DB_water_sensor.php");                   //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded"); //Specify content-type header

  int httpCode = http.POST(postData); //Send the request
  String payload = http.getString();  //Get the response payload

  //Serial.println("Temp Value=" + TempValueSend);
  //Serial.println("Humidity Value=" + HumiValueSend);
  //Serial.println("Heat index=" + HeatVauleSend);
  Serial.println(httpCode); //Print HTTP return code
  Serial.println(payload);  //Print request response payloadSS

  http.end(); //Close connection
  delay(4000);
}
