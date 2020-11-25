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
const char *host = "http://apipays.spairum.com/ReaderAPI/status/ReaderPro";
const char *addCard = "http://apipays.spairum.com/ReaderAPI/addCard/ReaderPro";
const char *card = "http://apipays.spairum.com/CardAPI";
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
  Serial.println("httpCode status=");
  Serial.print(httpCode);
  http.end();

  String httpRequestData, data;
  const char *id = "Mycard";
  int i = 1;
  i = 1+ i++;
  data = i;
  httpRequestData = "ID_Card=" + data;

  HTTPClient AddClient;

  AddClient.begin(addCard);
  AddClient.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int httpHit = AddClient.POST(httpRequestData); //Send the request
  String payloadHit = AddClient.getString();     //Get the response payloadHit

  // Serial.println(httpHit);    //Print HTTP return code
  if (httpHit > 0)
  { //Check the returning code

    String payloadHit = http.getString(); //Get the request response payload
    Serial.println(payloadHit);           //Print the response payload
  }
 // Serial.println(payloadHit); //Print request response payloadHit
  Serial.println("httpCode add=");
  Serial.print(httpHit);
  AddClient.end();            //Cl
  
   HTTPClient httpCard;
  httpCard.begin(card);
  int httpCode1 = http.GET();
  String payload1 = http.getString();
  if (httpCode1 > 0)
  { //Check the returning code

    String payload1 = httpCard.getString(); //Get the request response payload
    Serial.println(payload1);           //Print the response payload
  }
  Serial.println("httpCode card=");
  Serial.print(httpCode);

  http.end();
  delay(100);
  digitalWrite(Led_OnBoard, LOW);
  delay(500);
  digitalWrite(Led_OnBoard, HIGH);
}
