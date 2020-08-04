#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

const char *ssid = "LROA2GG"; 
const char *password = "12341234";  
const char* host = "script.google.com"; 
const char* fingerprint = "D8 4E 4F 08 10 7A FC A7 07 EA BF 2C 0B 4D 8C B9 F4 C5 7F EF";
String url;

void setup() 
{
  Serial.begin(115200);
  delay(100);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Netmask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
}

void loop() 
 {
 Serial.print("connecting to ");
  Serial.println(host);
 
  WiFiClientSecure client;

  const int httpPort = 443;
  if (!client.connect(host, httpPort)) 
  {
    Serial.println("connection failed");
    return;
  }
   float t = analogRead(A0);
  
  url = "/macros/s/AKfycbyiprphlw4VdZedIVvXttoFVkhIAKROomwO7tN7_2xh5lbBjqs/exec?func=addData&val="+ String(t);
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(500);
  String section="header";
  while(client.available())
  {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  Serial.println();
  Serial.println("closing connection");
  delay(6000);

}
