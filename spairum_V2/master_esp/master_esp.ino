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

int Led_OnBoard = 2;
const char *serverPost = "http://app.spairum.my.id/transfer/post/proto";
const char *serverGet = "http://app.spairum.my.id/transfer/get/proto";
const char *serverPostMesin = "http://app.spairum.my.id/mesin/edit/proto";

SoftwareSerial linkSerial(D6, D5); // (Rx, Tx)

int data1;
////#include "HX711.h"
//
//HX711 scale(D1, D2);              //DOUT, CLK
//float calibration_factor = 88; // this calibration factor is adjusted according to my load cell
//float GRAM;
//float KG;

void setup()
{
    // put your setup code here, to run once:
    delay(1000);
    pinMode(Led_OnBoard, OUTPUT);
    pinMode(0, INPUT); // LDR

    Serial.begin(115200);
    linkSerial.begin(115200);

//    while (!Serial)
//        continue;
//    WiFi.mode(WIFI_OFF); //Prevents reconnection issue (taking too long to connect)
//    delay(1000);
//    WiFi.mode(WIFI_STA); //This line hides the viewing of ESP as wifi hotspot
//    WiFi.begin(ssid, password);
//
    WiFiManager wifiManager;
    wifiManager.autoConnect("Spairum DWS");
    Serial.println("connected...yeey :)"); 
    Serial.println("Connecting");

//    while (WiFi.status() != WL_CONNECTED)
//    {
//        digitalWrite(Led_OnBoard, LOW);
//        delay(250);
//        Serial.print(".");
//        digitalWrite(Led_OnBoard, HIGH);
//        delay(500);
//    }

    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
    scale.set_scale();
    scale.tare();
    digitalWrite(Led_OnBoard, LOW);
    delay(2000);
    digitalWrite(Led_OnBoard, HIGH);
    delay(2000);
    StaticJsonDocument<500> doc;
}

void loop()
{
    getTrans();
    delay(1000);

    if (linkSerial.available())
    {
        // This one must be bigger than for the sender because it must store the strings
        StaticJsonDocument<200> doc;
        DeserializationError err = deserializeJson(doc, linkSerial);
        if (err == DeserializationError::Ok)
        {
            // Print the values
            // (we must use as<T>() to resolve the ambiguity)
            Serial.print("Token: ");
            data1 = doc["Sisa"];
            Serial.print(data1);
            postTrans();
        }
        else
        {
            Serial.print("deserializeJson() returned ");
            Serial.println(err.c_str());
            while (linkSerial.available() > 0)
                linkSerial.read();
        }
    }

    scale.set_scale(calibration_factor);
    GRAM = scale.get_units(), 4;
    Serial.print("berat");
    Serial.println(GRAM);
    Serial.println();
    KG = GRAM/1000;
    Serial.print("berat KG = ");
    Serial.println(KG);
int ind;
    if(GRAM > 2){
       ind = 3;
      }else if (GRAM > 1){
        ind = 2;
      } else
        ind = 1;
      

    String httpRequestMesin, isi, indikator;
    indikator = ind;
    isi = KG;
    httpRequestMesin = "isi=" + isi + "&indikator=" + indikator;

    HTTPClient httpMp; //Declare object of class HTTPClient

    httpMp.begin(serverPostMesin);                                         //Specify request destination
    httpMp.addHeader("Content-Type", "application/x-www-form-urlencoded"); //Specify content-type header

    int httpCode3 = httpMp.POST(httpRequestMesin); //Send the request
    String payload3 = httpMp.getString();          //Get the response payload

    Serial.println(httpCode3); //Print HTTP return code
    Serial.println(payload3);  //Print request response payload

    httpMp.end(); //Close connection

    delay(1000);
    digitalWrite(Led_OnBoard, LOW);
    delay(2000);
    digitalWrite(Led_OnBoard, HIGH);
}

void getTrans()
{
    HTTPClient client;
    client.begin(serverGet);

    int httpCode2 = client.GET();
    String payload2 = client.getString();

    Serial.print("Response Code:");
    Serial.println(httpCode2);
    Serial.println(payload2);

    if (httpCode2 > 0)
    {

        StaticJsonDocument<200> doc;

        auto error = deserializeJson(doc, payload2);
        if (error)
        {
            Serial.print(F("deserializeJson() failed with code "));
            Serial.println(error.c_str());
            return;
        }

        Serial.println(F("Response:"));
        Serial.println(doc["vaule"].as<char *>());
        serializeJson(doc, linkSerial);
    }
    client.end();
    delay(2000);
    digitalWrite(Led_OnBoard, LOW);
    delay(2000);
    digitalWrite(Led_OnBoard, HIGH);
}

void postTrans()
{
    //post Transfer
    Serial.println();
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
    digitalWrite(Led_OnBoard, LOW);
    delay(2000);
    digitalWrite(Led_OnBoard, HIGH);
}
