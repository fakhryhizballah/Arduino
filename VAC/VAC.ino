#include <Wire.h>
#include <LCD.h>
#include "RTClib.h"
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C  lcd(0x20,2,1,0,4,5,6,7); 

int VPIN;// initialise variable m
float VIN;//initialise variable n
const int sensorIn = A1;
int mVperAmp = 66; // use 100 for 20A Module and 66 for 30A Module
double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;
void setup()
{
  pinMode(A0,INPUT); // set pin a0 as input pin
  Serial.begin(9600);// begin serial communication between arduino and pc
  lcd.begin (16,2); // for 16 x 2 LCD module
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
}
void Volt(){
  VPIN=analogRead(A0);// read analog values from pin A0 across capacitor
   VIN=(VPIN*.3043052);// converts analog value(x) into input ac supply value using this formula ( explained in woeking section)
   Serial.print("ac voltage") ; // specify name to the corresponding value to be printed
   Serial.print(VIN) ; // prints the ac value on Serial monitor
   Serial.println();
 lcd.setCursor(0,1);
 lcd.print("Vrms=");
 lcd.print(VIN);
}
void AmperMeter(){
  
 Voltage = getVPP();
 VRMS = (Voltage/2.0) *0.707; 
 AmpsRMS = ((VRMS * 1000)/mVperAmp)-0.1;
 Serial.print(AmpsRMS);
 Serial.println(" Amps RMS");
 lcd.setCursor(0,0);
 lcd.print("Irms=");
 lcd.print(AmpsRMS);
}
float getVPP()
{
  float result;
  
  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 1000) //sample for 1 Sec
   {
       readValue = analogRead(sensorIn);
       // see if you have a new maxValue
       if (readValue > maxValue) 
       {
           /*record the maximum sensor value*/
           maxValue = readValue;
       }
       if (readValue < minValue) 
       {
           /*record the maximum sensor value*/
           minValue = readValue;
       }
   }
   
   // Subtract min from max
   result = ((maxValue - minValue) * 5.0)/1024.0;
      
   return result;
 }
 
void loop()
{
  AmperMeter();
  Volt();
}
