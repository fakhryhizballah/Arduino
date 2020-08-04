#include "DHTesp.h"   // Initialize Dht

#ifdef ESP32
#pragma message(THIS EXAMPLE IS FOR ESP8266 ONLY!)
#error Select ESP8266 board.
#endif

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

int Led_OnBoard = 2;                  // Initialize the Led_OnBoard 

const char* ssid = "Azimi";                  // Your wifi Name       
const char* password = "bismillah";          // Your wifi Password

const char *host = "103.253.212.155"; //Your pc or server (database) IP, example : 192.168.0.0 , if you are a windows os user, open cmd, then type ipconfig then look at IPv4 Address.

DHTesp dht;

void setup() {
	 // put your setup code here, to run once:
  delay(1000);
  pinMode(Led_OnBoard, OUTPUT);       // Initialize the Led_OnBoard pin as an output

  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) 
  {
    digitalWrite(Led_OnBoard, LOW);
    delay(250);
    Serial.print(".");
    digitalWrite(Led_OnBoard, HIGH);
    delay(250);
}

digitalWrite(Led_OnBoard, HIGH);
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.println("Connected to Network/SSID");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
  Serial.println();
  
  String thisBoard= ARDUINO_BOARD;
  Serial.println(thisBoard);
  dht.setup(13, DHTesp::DHT22); // Connect DHT sensor to GPIO 13 or D7

}

void loop() {
  // put your main code here, to run repeatedly:
	//delay(dht.getMinimumSamplingPeriod());
	  HTTPClient http;    //Declare object of class HTTPClient
 
  //String sensorData1,sensorData2, postData;
  //float Tempvalue=dht.getTemperature();  //Read Analog value of LDR
  //float Humivalue=dht.getHumidity();
  int Tempvalue=dht.getTemperature();  //Read Analog value of LDR
  int Humivalue=dht.getHumidity();


  //Post Data
  //postData ="Temp=" + sensorData1 + "&Humidity=" + sensorData2;
  //postData ="Temp=" + sensorData1;
  String TempValueSend, HumiValueSend, postData;

  //int ldrvalue=dht.getHumidity(); 
  TempValueSend = String(Tempvalue);
  HumiValueSend = String(Humivalue);
  postData = "Tempvalue=" + TempValueSend + "Humivalue" + HumiValueSend;

  //sensorData1=ldrvalue;

  //sensorData2=humidityvalue;

  http.begin("http://dht.spairum.com/insertDB.php");              //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
 
  int httpCode = http.POST(postData);   //Send the request
  String payload = http.getString();    //Get the response payload

  Serial.println("Temp Value=" + TempValueSend);
  Serial.println("Humidity Value=" + HumiValueSend);
  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payloadSS
  //Serial.println("LDR Value=" + sensorData1);
  //Serial.println("humidity Value=" + sensorData2);
  
  http.end();  //Close connection

  delay(4000);  //Here there is 4 seconds delay plus 1 second delay below, so Post Data at every 5 seconds
  digitalWrite(Led_OnBoard, LOW);
  delay(1000);
  digitalWrite(Led_OnBoard, HIGH);
  
}
