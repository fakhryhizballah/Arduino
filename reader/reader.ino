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
const char *host = "http://apipays.spairum.com/payApi";
const char *Postadd = "http://apipays.spairum.com/addReader";

int i = 2;
int y = 1; 
const char *re = "Mycard re";
const char *pw = "Mycard pw";
void setup() {
  delay(1000);
  pinMode(Led_OnBoard, OUTPUT);

  Serial.begin(115200);
  WiFiManager wifiManager;
 // wifiManager.autoConnect("AP-NAME", "AP-PASSWORD");
  wifiManager.autoConnect("Spairum NET", "12345678");
  Serial.println("connected...yeey :)");
  Serial.println("Connecting");
  digitalWrite(Led_OnBoard, HIGH);
}

void loop() {
  digitalWrite(Led_OnBoard, HIGH);
  delay(500);
  HTTPClient http;
  http.begin(host);
  int httpCode = http.GET();
  String payload = http.getString();
//  if (httpCode > 0)
//  { //Check the returning code
//
//    String payload = http.getString(); //Get the request response payload
//    Serial.println(payload);           //Print the response payload
//  }
//  else {
//    while (y>2){
//      digitalWrite(Led_OnBoard, LOW);
//      }
//    }
Serial.println(httpCode);
  http.end();
  digitalWrite(Led_OnBoard, LOW);
//  String httpRequestData, nama, password, Reader;
//  password = pw;
//  Reader = re;
//  nama = 2*i+1;
//  httpRequestData = "Nama=" + nama + "&Password=" + password + "&Reader" + Reader;
//  HTTPClient AddClient;
//  AddClient.begin(Postadd);
//  AddClient.addHeader("Content-Type", "application/x-www-form-urlencoded");
//
// int httpHit = AddClient.POST(httpRequestData); //Send the request
//  String payloadHit = AddClient.getString();     //Get the response payloadHit
// // Serial.println(httpHit);    //Print HTTP return code
//  if (httpHit > 0)
//  { //Check the returning code
//
//    String payloadHit = http.getString(); //Get the request response payload
//    Serial.println(payloadHit);           //Print the response payload
//  }
//  // Serial.println(payloadHit); //Print request response payloadHit
//  AddClient.end(); //Cl


}
