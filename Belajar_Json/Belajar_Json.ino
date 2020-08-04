#include <ArduinoJson.h>
//EXAMPLE HTTP REQUEST
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>


 
const char* ssid = "Azimi";
const char* password = "alhamdulillah";
 
void setup () {
 
  Serial.begin(115200);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
 
    delay(1000);
    Serial.println("Connecting..");
 
  }
 
}
 
void loop() {
 
  if (WiFi.status() == WL_CONNECTED) {
 
    HTTPClient http;
 
    http.begin("http://192.168.1.246/belajar_json/belajar.json");
    int httpCode = http.GET();
 
    if (httpCode > 0) {
      char json[500];
      String payload = http.getString();
      payload.toCharArray(json, 500);
      StaticJsonDocument<200> doc;
      deserializeJson(doc, json);

      const char* nama = doc["nama"];
      int umur = doc["umur"];

      Serial.print("parsing nama: ");
      Serial.println(nama);

      Serial.print("parsing umur: ");
      Serial.println(umur);
      
      //Serial.println(payload);
    }
 
    http.end();
 
   }
 
  delay(10000);
 
}
