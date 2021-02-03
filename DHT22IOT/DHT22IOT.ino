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

#include "DHT.h"
//Constants
#define DHTPIN D7     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

const char *host = "http://api.sensorku.tafexclusive.site/api/devices/TMP-999/data";
const char *host2 = "http://api.sensorku.tafexclusive.site/api/devices/TMP-911/data";


//Variables
int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value

int Led_OnBoard = 2;

void setup() {
//  pinMode(DHTPin, INPUT);
    dht.begin();
  
  pinMode(Led_OnBoard, OUTPUT);
  Serial.begin(115200);
  WiFiManager wifiManager;
 // wifiManager.autoConnect("AP-NAME", "AP-PASSWORD");
  wifiManager.autoConnect("TMP-999", "12345678");
  Serial.println("connected...yeey :)");
  Serial.println("Connecting");
  digitalWrite(Led_OnBoard, HIGH);

}

void loop() {
  digitalWrite(Led_OnBoard, HIGH);
    //Read data and store it to variables hum and temp
    hum = dht.readHumidity();
    temp= dht.readTemperature();
    //Print temp and humidity values to serial monitor
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius");
  delay(1000);
  digitalWrite(Led_OnBoard, LOW);
  String httpRequestData, httpRequestData2, temperatur, humm;
  temperatur = temp;
  humm = hum;
  httpRequestData = "value=" + temperatur ;
  httpRequestData2 = "value=" + humm ;
  HTTPClient http;
  http.begin(host);
  http.addHeader("Authorization", "Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiJ9.eyJhdWQiOiIyIiwianRpIjoiNzc0YjFhZDg4YzM2ZTZjM2EyYWE1NDU5ZmEwMDRlMTAzNDhhN2M5MjdiMzRhNDAzZjc5ZjU4M2I5ZTQ3MmRlZjZkNGUxODk1OGRhYmFmMDQiLCJpYXQiOjE2MDgwMDQ2MjgsIm5iZiI6MTYwODAwNDYyOCwiZXhwIjoxNjM5NTQwNjI4LCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.r2p-_g_OPypqJGr9IxLwlk07ZoeMuWEDzhj2XrvgFhLzDHVxAZnBeE_YFG4giWPS5Q-XC6pUSgPnAmtXcxfQIkRhbC3aBF--k7dLFuBlPYF4MwPwZfWIlNUaHhBBXqwfhjvr-f1N8TTIolI5Z0MWeC62irE5drmlDZ5lnJUQJAbq2ybRVkuWlKSDkkVg8ixlalAgWkGTH5ezZRxWCcQMC0WSPywocvoYATPGcFsxv9iyKdbM-RX5-eX9oGw3sYy-bjl50mgBTHOr7-F4jWvqqmMr2KsMXje1yT0b-VzsdLel_w3j9C0V4jNcfrVkson3s2bXvIZKitEDYY3ckVgTodu-78-kdy1bkoEtapYV006Konsg271okZUa2-UUsqaX6t9b828ak5LnmYuspqGcWeBKadJ4yHXSXAw1wLQ28LPRsKyiQdl9RkzyAUS9Oms8frDAfoDY0_7Ubv8uoNWRNo2gnhuakbqCW4MmzhIsY2Q03SmCYm6v1GqAtjj-daa9Dpr_5HkswXNDq8AZTbkOXRPyVaGP4Z1sXucKveyV1PYesTACabSCaY3ovR2tGIMFp4TqycNaBHtLjfJ1iCpVhU2QyyR2uagYYBG0U_uvJ94Je_8q-77Djz9uxG9pBAWhI02HyN6WfuxYOwrDFO8KJtC0CAbTVJhHvQN1rB0nzLs");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpHit = http.POST(httpRequestData);
  String payload = http.getString();
  Serial.println(httpHit);
  http.end();
//  HTTPClient http;
  http.begin(host2);
  http.addHeader("Authorization", "Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiJ9.eyJhdWQiOiIyIiwianRpIjoiNzc0YjFhZDg4YzM2ZTZjM2EyYWE1NDU5ZmEwMDRlMTAzNDhhN2M5MjdiMzRhNDAzZjc5ZjU4M2I5ZTQ3MmRlZjZkNGUxODk1OGRhYmFmMDQiLCJpYXQiOjE2MDgwMDQ2MjgsIm5iZiI6MTYwODAwNDYyOCwiZXhwIjoxNjM5NTQwNjI4LCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.r2p-_g_OPypqJGr9IxLwlk07ZoeMuWEDzhj2XrvgFhLzDHVxAZnBeE_YFG4giWPS5Q-XC6pUSgPnAmtXcxfQIkRhbC3aBF--k7dLFuBlPYF4MwPwZfWIlNUaHhBBXqwfhjvr-f1N8TTIolI5Z0MWeC62irE5drmlDZ5lnJUQJAbq2ybRVkuWlKSDkkVg8ixlalAgWkGTH5ezZRxWCcQMC0WSPywocvoYATPGcFsxv9iyKdbM-RX5-eX9oGw3sYy-bjl50mgBTHOr7-F4jWvqqmMr2KsMXje1yT0b-VzsdLel_w3j9C0V4jNcfrVkson3s2bXvIZKitEDYY3ckVgTodu-78-kdy1bkoEtapYV006Konsg271okZUa2-UUsqaX6t9b828ak5LnmYuspqGcWeBKadJ4yHXSXAw1wLQ28LPRsKyiQdl9RkzyAUS9Oms8frDAfoDY0_7Ubv8uoNWRNo2gnhuakbqCW4MmzhIsY2Q03SmCYm6v1GqAtjj-daa9Dpr_5HkswXNDq8AZTbkOXRPyVaGP4Z1sXucKveyV1PYesTACabSCaY3ovR2tGIMFp4TqycNaBHtLjfJ1iCpVhU2QyyR2uagYYBG0U_uvJ94Je_8q-77Djz9uxG9pBAWhI02HyN6WfuxYOwrDFO8KJtC0CAbTVJhHvQN1rB0nzLs");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  httpHit = http.POST(httpRequestData2);
  payload = http.getString();
  Serial.println(httpHit);
  http.end();
  delay(2000);
}
