#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

int Led_OnBoard = 2;

int flowRate;
int y = 5;


// GPIO where the DS18B20 is connected to
const int oneWireBus = 4;     

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

// Wifi config


const char *ssid = "Azimi";             // Your wifi Name
const char *password = "alhamdulillah"; // Your wifi Password
const char *host = "103.253.212.155"; //Your pc or server (database) IP, example : 192.168.0.0 , if you are a windows os user, open cmd, then type ipconfig then look at IPv4 Address.

void setup(){
  delay(1000);
  pinMode(Led_OnBoard, OUTPUT);
  pinMode(0,INPUT); // LDR

  
  Serial.begin(115200);
   sensors.begin();
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
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

  
  
  }

void loop(){
sensors.requestTemperatures(); 
  float temperatureC = sensors.getTempCByIndex(0);
  //float temperatureF = sensors.getTempFByIndex(0);
  Serial.print("Temperatur :");
  Serial.print(temperatureC);
  Serial.println("ºC");
  //Serial.print(temperatureF);
  //Serial.println("ºF");
  HTTPClient http; //Declare object of class HTTPClient
  int ldr=analogRead(0);
  Serial.print("LDR: ");
  Serial.print(ldr);
  Serial.println(" lux");

  String TempValueSend,postData, Debit, LDR, TurbidityVaule;

  TempValueSend = String(temperatureC);
  Debit = String(flowRate);
  LDR = String(ldr);
  TurbidityVaule = String(y);
  
  

  postData = "Tvalue=" + TempValueSend + "&Flow=" + Debit + "&Ldr=" + LDR + "&Turbidity=" + TurbidityVaule;

  http.begin("http://dht.spairum.com/DB_water_sensor.php");                   //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded"); //Specify content-type header

  int httpCode = http.POST(postData); //Send the request
  String payload = http.getString();  //Get the response payload

  Serial.println(httpCode); //Print HTTP return code
  Serial.println(payload);  //Print request response payloadSS

  http.end(); //Close connection
  digitalWrite(Led_OnBoard, LOW);
    delay(250);
    Serial.print(".");
    digitalWrite(Led_OnBoard, HIGH);
    delay(500);
  delay(4000);
}
