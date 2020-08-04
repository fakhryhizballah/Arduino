#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <DNSServer.h>
#include <WiFiManager.h>   

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
WiFiManager wifiManager;

}

void loop() {
  
  wifiManager.autoConnect("AutoConnectAP");
  Serial.println("connected...yeey :)");

}
