#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DNSServer.h>
#include <WiFiManager.h>
#include <ArduinoJson.h>
#include <Arduino_JSON.h>
#include "EspMQTTClient.h"

//EspMQTTClient client(
//  "Iconplus2",      //WifiSSID
//  "1c0nplus2",      //WifiPassword
//  "47.254.251.29",  // MQTT Broker server ip
//  "spairum",        // Can be omitted if not needed MQTTUsername
//  "broker",         // Can be omitted if not needed MQTTPassword
//  "TestClient",     // Client name that uniquely identify your device
//  1883              // The MQTT port, default to 1883. this line can be omitted
//);

EspMQTTClient client(
  "ws.spairum.my.id",  // MQTT Broker server ip
  1883,            // The MQTT port, default to 1883. this line can be omitted
  "spairum",        // Can be omitted if not needed MQTTUsername
  "broker",         // Can be omitted if not needed MQTTPassword
  "TestClient"     // Client name that uniquely identify your device
);


int Led_OnBoard = 2;
//WiFiClient espClient;
//PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  pinMode(Led_OnBoard, OUTPUT);
  WiFiManager wifiManager;
  wifiManager.autoConnect("Nama Wifi", "12345678");
  Serial.println("Connecting");
  digitalWrite(Led_OnBoard, HIGH);
  delay(2000);
  
  client.enableDebuggingMessages(); // Enable debugging messages sent to serial output
  client.enableHTTPWebUpdater(); // Enable the web updater. User and password default to values of MQTTUsername and MQTTPassword. These can be overrited with enableHTTPWebUpdater("user", "password").
  client.enableLastWillMessage("Test", "I am going offline");  // You can activate the retain flag by setting the third parameter to true

}
void onConnectionEstablished()
{
  // Subscribe to "mytopic/test" and display received message to Serial
    client.subscribe("test", [](const String & payload) {
    Serial.println(payload);
    if ((payload) == "oke"){
      digitalWrite(Led_OnBoard, LOW);
      delay(100);
      digitalWrite(Led_OnBoard, HIGH);
      };
      
    StaticJsonDocument<96> doc;
    DeserializationError error = deserializeJson(doc, payload);

  if (error) {
  Serial.println(F("deserializeJson() failed: "));
  return;
  }

  int mqtt_dashboard_brightness = doc["mqtt_dashboard"]["brightness"]; // 100
  long mqtt_dashboard_color = doc["mqtt_dashboard"]["color"]; // -7434610);
  
  Serial.println(mqtt_dashboard_brightness);
  
  });

//  // Subscribe to "mytopic/wildcardtest/#" and display received message to Serial
//  client.subscribe("mytopic/wildcardtest/#", [](const String & topic, const String & payload) {
//    Serial.println("(From wildcard) topic: " + topic + ", payload: " + payload);
//  });

  // Publish a message to "mytopic/test"
  client.publish("test", "This is a message"); // You can activate the retain flag by setting the third parameter to true

  // Execute delayed instructions
     client.executeDelayed(5 * 1000, []() {
    client.publish("mytopic/wildcardtest/test123", "This is a message sent 5 seconds later");
  });
}

int i=1;
void loop() {
  // put your main code here, to run repeatedly:
  client.loop();
  i = 1+i ;
 Serial.print("count: ");
 Serial.println(i);
 String counts;
 counts = i;
 delay(100);
 client.publish("test", counts); // You can activate the retain flag by setting the third parameter to true

 
 
  
}
