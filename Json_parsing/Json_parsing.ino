#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include <Wire.h>

int Led_OnBoard = 2;
// Wifi config

const char *ssid = "Azimi";             // Your wifi Name
const char *password = "alhamdulillah"; // Your wifi Password

const char *host = "http://192.168.1.246/Mesin/detail/COV0001PNK002";

void setup()
{
  // put your setup code here, to run once:
  delay(1000);
  pinMode(Led_OnBoard, OUTPUT);
  pinMode(0, INPUT); // LDR

  Serial.begin(115200);

  while (!Serial)
    continue;
  WiFi.mode(WIFI_OFF); //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA); //This line hides the viewing of ESP as wifi hotspot
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
  digitalWrite(Led_OnBoard, LOW);
  delay(2000);
  digitalWrite(Led_OnBoard, HIGH);
  delay(2000);
}

void loop()
{
  HTTPClient http; //Declare object of class HTTPClient

  Serial.print("Request Link:");
  Serial.println(host);

  http.begin(host); //Specify request destination

  int httpCode = http.GET();         //Send the request
  String payload = http.getString(); //Get the response payload from server

  Serial.print("Response Code:"); //200 is OK
  Serial.println(httpCode);       //Print HTTP return code

  Serial.print("Returned data from Server:");
  Serial.println(payload); //Print request response payload

  if (httpCode == 200)
  {
    // Allocate JsonBuffer
    // Use arduinojson.org/assistant to compute the capacity.
    // const size_t capacity = JSON_OBJECT_SIZE(3) + JSON_ARRAY_SIZE(2) + 60;
    DynamicJsonDocument doc(1024);

    // Parse JSON object
    //    JsonObject& root = jsonBuffer.parseObject(payload);
    //    if (!root.success()) {
    //      Serial.println(F("Parsing failed!"));
    //      return;
    //    }
    auto error = deserializeJson(doc, payload);
    if (error)
    {
      Serial.print(F("deserializeJson() failed with code "));
      Serial.println(error.c_str());
      return;
    }

    // Decode JSON/Extract values
    Serial.println(F("Response:"));
    Serial.println(doc["id"].as<char *>());
    Serial.println(doc["isi"].as<char *>());
    Serial.println(doc["indikator"].as<char *>());
    //    Serial.println(doc["data"][1].as<char*>());
  }
  else
  {
    Serial.println("Error in response");
  }

  http.end(); //Close connection

  delay(5000); //GET Data at every 5 seconds
}
