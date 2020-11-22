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

int Led_OnBoard = 2;
// Wifi config
const char *host = "http://pay.spairum.com/ReaderAPI/status/ReaderPro2";
const char *addCard = "http://pay.spairum.com/ReaderAPI/addCard/ReaderPro2";
const int httpsPort = 443;

void setup()
{
  delay(1000);
  pinMode(Led_OnBoard, OUTPUT);

  Serial.begin(115200);
  WiFiManager wifiManager;
  wifiManager.autoConnect("Spairum NET");
  Serial.println("connected...yeey :)");
  Serial.println("Connecting");
}

void loop()
{
  HTTPClient http;
  http.begin(host);
  int httpCode = http.GET();
  String payload = http.getString();
  if (httpCode > 0)
  { //Check the returning code

    String payload = http.getString(); //Get the request response payload
    Serial.println(payload);           //Print the response payload
  }

  http.end();
  delay(1000);
  digitalWrite(Led_OnBoard, LOW);
  delay(1000);
  digitalWrite(Led_OnBoard, HIGH);

  String httpRequestData, data;
  const char *id = "Mycard";
  data = id;
  httpRequestData = "ID_Card=" + data;

  HTTPClient AddClient;

  AddClient.begin(addCard);
  AddClient.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int httpHit = AddClient.POST(httpRequestData); //Send the request
  String payloadHit = AddClient.getString();     //Get the response payloadHit

  Serial.println(httpHit);    //Print HTTP return code
  Serial.println(payloadHit); //Print request response payloadHit
  AddClient.end();            //Cl
  delay(1000);
  digitalWrite(Led_OnBoard, LOW);
  delay(1000);
  digitalWrite(Led_OnBoard, HIGH);
}
