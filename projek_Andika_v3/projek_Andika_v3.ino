//#include <ESP8266WiFi.h>
#include <WiFiClient.h>
//#include <ESP8266HTTPClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include <WiFi.h>
#include <HTTPClient.h>

int Led_OnBoard = 2;
int sLDR = 36;
int sTurbidity = 39;
//int flowRate;
int y = 5;

TaskHandle_t Task1;

byte sensorInterrupt = 0; // 0 = digital pin 2
byte sensorPin = 34;

// The hall-effect flow sensor outputs approximately 4.5 pulses per second per
// litre/minute of flow.
float calibrationFactor = 99;

volatile byte pulseCount;

float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;

unsigned long oldTime;

// GPIO where the DS18B20 is connected to
const int oneWireBus = 5;

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature sensors(&oneWire);

// Wifi config

const char *ssid = "Azimi";             // Your wifi Name
const char *password = "alhamdulillah"; // Your wifi Password
const char *host = "103.253.212.155";   //Your pc or server (database) IP, example : 192.168.0.0 , if you are a windows os user, open cmd, then type ipconfig then look at IPv4 Address.

void setup()
{
  delay(1000);
  pinMode(Led_OnBoard, OUTPUT);
  pinMode(sLDR, INPUT);       // LDR
  pinMode(sTurbidity, INPUT); //Turbidity

  Serial.begin(115200);
  sensors.begin();
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

  xTaskCreatePinnedToCore(
      Task1code, /* Task function. */
      "Task1",   /* name of task. */
      10000,     /* Stack size of task */
      NULL,      /* parameter of the task */
      1,         /* priority of the task */
      &Task1,    /* Task handle to keep track of created task */
      0);        /* pin task to core 0 */
  delay(500);
}

void loop()
{
  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0);
  //float temperatureF = sensors.getTempFByIndex(0);
  Serial.print("Temperatur :");
  Serial.print(temperatureC);
  Serial.println("ºC");
  //Serial.print(temperatureF);
  //Serial.println("ºF");
  HTTPClient http; //Declare object of class HTTPClient
  int ldr = analogRead(sLDR);
  int turbidity = analogRead(sTurbidity);
  Serial.print("LDR: ");
  Serial.print(ldr, DEC);
  Serial.println(" lux");
  Serial.print("Turbidity: ");
  Serial.println(turbidity);
  Serial.print("Flow Sensor");
  //Serial.println(flowSen);

  String TempValueSend, postData, Debit, LDR, TurbidityVaule;

  TempValueSend = String(temperatureC);
  Debit = String(flowRate);
  LDR = String(ldr);
  TurbidityVaule = String(turbidity);

  postData = "Tvalue=" + TempValueSend + "&Flow=" + Debit + "&Ldr=" + LDR + "&Turbidity=" + TurbidityVaule;

  http.begin("http://dht.spairum.com/DB_water_sensor.php");            //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded"); //Specify content-type header

  int httpCode = http.POST(postData); //Send the request
  String payload = http.getString();  //Get the response payload

  Serial.println(httpCode); //Print HTTP return code
  Serial.println(payload);  //Print request response payloadSS

  http.end(); //Close connection
  digitalWrite(Led_OnBoard, LOW);
  digitalWrite(Led_OnBoard, HIGH);
  delay(500);
  delay(4000);
}

void Task1code(void *pvParameters)
{
  Serial.print("Task1 running on core ");
  Serial.println(xPortGetCoreID());

  pinMode(sensorPin, INPUT);
  digitalWrite(sensorPin, HIGH);

  pulseCount = 0;
  flowRate = 0.0;
  flowMilliLitres = 0;
  totalMilliLitres = 0;
  oldTime = 0;

  // The Hall-effect sensor is connected to pin 2 which uses interrupt 0.
  // Configured to trigger on a FALLING state change (transition from HIGH
  // state to LOW state)
  attachInterrupt(sensorInterrupt, pulseCounter, FALLING);

  for (;;)
  {
    if ((millis() - oldTime) > 1000) // Only process counters once per second
    {
      // Disable the interrupt while calculating flow rate and sending the value to
      // the host
      detachInterrupt(sensorInterrupt);

      // Because this loop may not complete in exactly 1 second intervals we calculate
      // the number of milliseconds that have passed since the last execution and use
      // that to scale the output. We also apply the calibrationFactor to scale the output
      // based on the number of pulses per second per units of measure (litres/minute in
      // this case) coming from the sensor.
      flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;

      // Note the time this processing pass was executed. Note that because we've
      // disabled interrupts the millis() function won't actually be incrementing right
      // at this point, but it will still return the value it was set to just before
      // interrupts went away.
      oldTime = millis();

      // Divide the flow rate in litres/minute by 60 to determine how many litres have
      // passed through the sensor in this 1 second interval, then multiply by 1000 to
      // convert to millilitres.
      flowMilliLitres = (flowRate / 60) * 1000;

      // Add the millilitres passed in this second to the cumulative total
      totalMilliLitres += flowMilliLitres;

      unsigned int frac;

      // Print the flow rate for this second in litres / minute
      Serial.print("Flow rate: ");
      Serial.print(int(flowRate)); // Print the integer part of the variable
      Serial.print("L/min");
      Serial.print("\t"); // Print tab space

      // Print the cumulative total of litres flowed since starting
      Serial.print("Output Liquid Quantity: ");
      Serial.print(totalMilliLitres);
      Serial.println("mL");
      Serial.print("\t"); // Print tab space
      Serial.print(totalMilliLitres / 1000);
      Serial.print("L");

      // Reset the pulse counter so we can start incrementing again
      pulseCount = 0;

      // Enable the interrupt again now that we've finished sending output
      attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
    }
  }
}
/*
Insterrupt Service Routine
 */
void pulseCounter()
{
  // Increment the pulse counter
  pulseCount++;
}
