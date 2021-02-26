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

const char *serverPost = "http://app.spairum.my.id/transfer/post/apotes";
const char *serverGet = "http://app.spairum.my.id/transfer/get/apotes";
const char *serverPostMesin = "http://app.spairum.my.id/mesin/edit/apotes";


int Led_OnBoard = 2;
int data1 = 1;
int nilai = 1;
// Wifi config
void setup() {
    Serial.begin(115200);
    pinMode(Led_OnBoard, OUTPUT);
  Serial.begin(115200);
  WiFiManager wifiManager;
  wifiManager.autoConnect("spairum tes");
  Serial.println("connected...yeey :)");
  Serial.println("Connecting");
  digitalWrite(Led_OnBoard, HIGH);
    Serial.println(WiFi.localIP());
    digitalWrite(Led_OnBoard, LOW);
    delay(2000);
    digitalWrite(Led_OnBoard, HIGH);
    delay(2000);
}

void loop() {

  nilai = nilai + 1;
  String httpRequestMesin, isi, indikator;
    indikator = 1;
    isi = nilai;
    httpRequestMesin = "isi=" + isi + "&indikator=" + indikator;

    HTTPClient httpMp; //Declare object of class HTTPClient

    httpMp.begin(serverPostMesin);                                         //Specify request destination
    httpMp.addHeader("Content-Type", "application/x-www-form-urlencoded"); //Specify content-type header

    int httpCode3 = httpMp.POST(httpRequestMesin); //Send the request
    String payload3 = httpMp.getString();          //Get the response payload

    Serial.println(httpCode3); //Print HTTP return code
    Serial.println(payload3);  //Print request response payload

    httpMp.end(); //Close connection

    
    data1 = 1 + data1;
    Serial.println (data1);
    delay(1000);
     String httpRequestData, data2;
    data2 = data1;
    httpRequestData = "vaule=" + data2;

    HTTPClient http; //Declare object of class HTTPClient

    http.begin(serverPost);                                              //Specify request destination
    http.addHeader("Content-Type", "application/x-www-form-urlencoded"); //Specify content-type header

    int httpCode = http.POST(httpRequestData); //Send the request
    String payload = http.getString();         //Get the response payload

    Serial.println(httpCode); //Print HTTP return code
    Serial.println(payload);  //Print request response payload

    http.end(); //Close connection

    delay(1000);

}
