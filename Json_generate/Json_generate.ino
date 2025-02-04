#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
//#include <SoftwareSerial.h>
#include <Wire.h>

int Led_OnBoard = 2;
// Wifi config

const char *ssid = "Azimi";             // Your wifi Name
const char *password = "alhamdulillah"; // Your wifi Password

const char *serverName = "https://apps.spairum.com/mesin/edit/COV0001PNK002";
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
  // Allocate JsonBuffer

  //StaticJsonDocument<200> doc;
  DynamicJsonDocument doc(1024);

  // Start a new line
  Serial.println();
  // serializeJsonPretty(doc, input);
  // JsonObject obj = doc.as<JsonObject>();
  String air, ind, httpRequestData;
  air = 10000;
  ind = 1;
  httpRequestData = "isi=" + air + "&indikator=" + ind;

  HTTPClient http; //Declare object of class HTTPClient

  http.begin(serverName);                                              //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded"); //Specify content-type header

  int httpCode = http.POST(httpRequestData); //Send the request
  String payload = http.getString();         //Get the response payload

  Serial.println(httpCode); //Print HTTP return code
  Serial.println(payload);  //Print request response payload

  http.end(); //Close connection
  delay(1500);
  digitalWrite(Led_OnBoard, LOW);
  delay(1000);
  digitalWrite(Led_OnBoard, HIGH);
}
