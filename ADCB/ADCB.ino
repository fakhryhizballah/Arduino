//LCD config
#include <Wire.h>
#include <LCD.h>
#include "RTClib.h"
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C  lcd(0x20,2,1,0,4,5,6,7);   //sometimes the adress is not 0x3f. Change to 0x27 if it dosn't work.
////////////////////////////////////////////////////////////////////////////////////////////////////////

char data = 0;
String voice;
int tl1 = 2;
int tl2 = 3;
int tl3 = 4;
int tl4 = 5;

void setup(){
   Serial.begin(9600);
   lcd.begin (16,2); // for 16 x 2 LCD module
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  pinMode (tl1, OUTPUT);
  pinMode (tl2, OUTPUT);
  pinMode (tl3, OUTPUT);
  pinMode (tl4, OUTPUT);
  pinMode (13, OUTPUT);
   }

//Ampere Meter
const int analogchannel = 2; //Connect current sensor with A2 of Arduino
int sensitivity = 66; // use 100 for 20A Module and 66 for 30A Module
int adcvalue= 0;
int offsetvoltage = 2500; 
double Voltage = 0; //voltage measuring
double ecurrent = 0;// Current measuring
float outputValue= 0;
double amps= 0;

//Volt meter
int analogInput = 0;
float vout = 0;
float vin = 0;
int vol = 0;
float R1 = 100000.0; // resistance of R1 (100K) -see text!
float R2 = 10000.0; // resistance of R2 (10K) - see text!

// daya
float daya= 0;

//watt hours
unsigned long msec = 0;
float time = 0.0;
int sample = 0;
float totalCharge = 0.0;
float averageAmps = 0.0;
float ampSeconds = 0.0;
float ampHours = 0.0;
float wattHours = 0.0;
   
void amper(){
  //Amper Meter 
 adcvalue = analogRead(analogchannel);//reading the value from the analog pin
 Voltage = (adcvalue / 1024.0) * 5000; // Gets you mV
 ecurrent = ((Voltage - offsetvoltage) / sensitivity);
//Prints on the serial port
 lcd.setCursor(0,0);
 lcd.print("I=");
 lcd.print(ecurrent);
 lcd.print("A"); //unit for the current to be measured
}

void volt(){
  //Volt Meter
 vol = analogRead(analogInput);
   vout = (vol * 5.0) / 1024.0; // see text
   vin = vout /(R2/(R1+R2)); 
   if (vin<0.09) {
   vin=0;//statement to quash undesired reading !
   } 
lcd.setCursor(0, 1);
lcd.print("V=");
lcd.print(vin,1);
lcd.print("V");
//Serial.print("volt");
//Serial.print(vin,1);
//Serial.print("V");
}

void dayaDisp(){
   daya=(vin*ecurrent);
 lcd.setCursor(8,0);
 lcd.print("P=");
 lcd.print(daya);
 lcd.print("W");
};

void wattH(){
 float watts = ecurrent * vin;
sample = sample + 1;
msec = millis();
time = (float) msec / 1000.0;
totalCharge = totalCharge + ecurrent;
averageAmps = totalCharge / sample;
ampSeconds = averageAmps*time;
ampHours = ampSeconds/3600;
wattHours = vin * ampHours;
//Serial.print("E");
//Serial.print(wattHours);
//Serial.print("Wh");
//Serial.print("\n");
 lcd.setCursor(8,1);
 lcd.print("E=");
 lcd.print(wattHours);
 lcd.print("Wh");
 //Serial.print("\n");
}
void setTL(){
   if(Serial.available() > 0)      // Send data only when you receive data:
   {
      data = Serial.read();        //Read the incoming data & store into data
      Serial.print(data);          //Print Value inside data in Serial monitor
      Serial.print("\n");
    //Indikator L. 1 and 0        
      if(data == '1')              
         digitalWrite(13, HIGH);
      else if(data == '0')         
         digitalWrite(13, LOW);
    //Tl1. 2 and 3
      else if(data == '2')
      {
        //lcd.setCursor(0,0);         
        digitalWrite(tl1, HIGH);
        //Serial.print("Lampu Mati");
        //lcd.write("Lampu Mati");
      } 
      else if(data == '3')
      {
        //lcd.setCursor(0,0);         
        digitalWrite(tl1, LOW);
        //lcd.print("Lampu Hidup");
      } 
   //Tl2. 4 and 5     
      else if(data == '4')
      {
        digitalWrite(tl2, HIGH);
      }
      else if(data == '5')
      {      
        digitalWrite(tl2, LOW);
      }
    //Tl3. 6 and 7     
      else if(data == '6')
      {
        digitalWrite(tl3, HIGH);
      }
      else if(data == '7')
      {     
        digitalWrite(tl3, LOW);
      }
    //Tl4. 8 and 9     
      else if(data == '8')
      {
        digitalWrite(tl4, HIGH);
      }
      else if(data == '9')
      {         
        digitalWrite(tl4, LOW);
      } 
  }
}
void comentTL(){
  Serial.println(voice);
  if (Serial.available()){
    }
  }

void loop() {
  comentTL();
 
  amper();
  volt();
  dayaDisp();
  wattH();

 delay(250);//delay of 0.5 sec
 lcd.clear();

}
