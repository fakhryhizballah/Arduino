#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_ADS1015.h>

#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <DNSServer.h>
#include <WiFiManager.h> 
 
Adafruit_ADS1115 ads;

SoftwareSerial linkSerial(D6, D5); // (Rx, Tx)

int Led_OnBoard = 2;

int data1;
int data2;
int y = 5;


// GPIO where the DS18B20 is connected to
const int oneWireBus = 15;

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature sensors(&oneWire);

// Wifi config

//const char *ssid = "SpairumNet";             // Your wifi Name
//const char *password = "12341234"; // Your wifi Password
const char *host = "103.253.212.155";   //Your pc or server (database) IP, example : 192.168.0.0 , if you are a windows os user, open cmd, then type ipconfig then look at IPv4 Address.

void setup()
{
  delay(1000);
  pinMode(Led_OnBoard, OUTPUT);
  pinMode(0, INPUT); // LDR

  Serial.begin(115200);
  sensors.begin();
  linkSerial.begin(115200);
  //ads.setGain(GAIN_TWO); 
  ads.begin();

   WiFiManager wifiManager;
  wifiManager.autoConnect("AutoConnectAP");
  Serial.println("connected...yeey :)");
  
//  while (!Serial) continue;
//  WiFi.mode(WIFI_OFF); //Prevents reconnection issue (taking too long to connect)
//  delay(1000);
//  WiFi.mode(WIFI_STA); //This line hides the viewing of ESP as wifi hotspot
//  WiFi.begin(ssid, password);
//  Serial.println("Connecting");

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
  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0);
  Serial.print("Temperatur :");
  Serial.print(temperatureC);
  Serial.println("ºC");

  int16_t adc0, adc1;
 
 adc0 = ads.readADC_SingleEnded(0);
 adc1 = ads.readADC_SingleEnded(1);
int ldr = analogRead(0);
Serial.print("LDR 1: ");
Serial.println(ldr);
  Serial.print("LDR: ");
  Serial.print(adc0);
  Serial.println(" lux");
  Serial.print("Turbidity: ");
  Serial.println(adc1);

  if (linkSerial.available()){
    // This one must be bigger than for the sender because it must store the strings
    StaticJsonDocument<300> doc;
    DeserializationError err = deserializeJson(doc, linkSerial);
    if (err == DeserializationError::Ok) 
    {
      // Print the values
      // (we must use as<T>() to resolve the ambiguity)
      Serial.print("Flow rate: ");
      data1=doc["flowR"];
      Serial.print(data1);
      Serial.print("L/min");
      Serial.print("\t");
      Serial.print("Output Liquid Quantity: ");
      data2=doc["data2"];
      Serial.print(data2);
      Serial.println("mL");
      /**
      Serial.print("timestamp = ");
      Serial.println(doc["timestamp"].as<long>());
      Serial.print("value = ");
      Serial.println(doc["value"].as<int>());
        **/
    } 
    else 
    {
      // Print error to the "debug" serial port
      Serial.print("deserializeJson() returned ");
      Serial.println(err.c_str());
  
      // Flush all bytes in the "link" serial port buffer
      while (linkSerial.available() > 0)
        linkSerial.read();
      
    }
   }
  /**
  Serial.print("Flow rate: ");
  int data1=root["flowR"];
  Serial.print(data1);
  Serial.print("L/min");
  Serial.print("\t");
  Serial.print("Output Liquid Quantity: ");
  int data2=root["hum"];
  Serial.print(totalML);
  Serial.println("mL");
  **/

  HTTPClient http; //Declare object of class HTTPClient



  String TempValueSend, postData, Debit, LDR, TurbidityVaule;

  TempValueSend = String(temperatureC);
  Debit = String(data1);
  LDR = String(adc0);
  TurbidityVaule = String(adc1);

  postData = "Tvalue=" + TempValueSend + "&Flow=" + Debit + "&Ldr=" + LDR + "&Turbidity=" + TurbidityVaule;

  http.begin("http://dht.spairum.com/DB_water_sensor.php");            //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded"); //Specify content-type header

  int httpCode = http.POST(postData); //Send the request
  String payload = http.getString();  //Get the response payload

  Serial.println(httpCode); //Print HTTP return code
  Serial.println(payload);  //Print request response payloadSS

  http.end(); //Close connection
  digitalWrite(Led_OnBoard, LOW);
  delay(250);
  digitalWrite(Led_OnBoard, HIGH);
  delay(500);
  delay(4000);
}
