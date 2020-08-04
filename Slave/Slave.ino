#include <SoftwareSerial.h>
#include <EEPROM.h>     // We are going to read and write PICC's UIDs from/to EEPROM
#include <SPI.h>        // RC522 Module uses SPI protocol
#include <MFRC522.h>
#include <Servo.h>
Servo myservo;
int pos = 0;

#define RST_PIN 9
#define SS_PIN 10 //MFRC522 pin
MFRC522 rfid(SS_PIN, RST_PIN);
String uidString;
const int pinSensor = 5;
const int pinBuzzer = 4;
const int pinLed = 6;
const int pinBtn = 7;
int valBtn = 0;
boolean data;

SoftwareSerial sim(3, 2);
int _timeout;
String _buffer;
String number = "+6281998081123"; //-> No

void setup() {
  myservo.attach(8);  // attaches the servo

  pinMode(pinSensor, INPUT);
  pinMode(pinBuzzer, OUTPUT);
  digitalWrite(pinBuzzer, LOW);
  pinMode(pinLed, OUTPUT);
  digitalWrite(pinLed,HIGH); //Led kunci off
  pinMode(pinBtn, INPUT);

  delay(5000);
  Serial.begin(9600);
  _buffer.reserve(50);
  Serial.println("Sistem Started...");
  sim.begin(9600);
  delay(1000);
  Serial.println("Sim Siap");

  SPI.begin(); //SPI buttonIsi
  rfid.PCD_Init(); //MFRC522
  rfid .PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));

}

void loop() {
  /*data = digitalRead(pinSensor);
  if (data==0){
    digitalWrite(pinBuzzer, LOW);
    if (Serial.available() > 0)
    callNumber();
    delay(30000);
  } else{
    digitalWrite(pinBuzzer, HIGH);
  }*/
  if(rfid.PICC_IsNewCardPresent()) {

    readRFID();
  }
  /*
  valBtn = digitalRead(pinBtn);
  if (valBtn==LOW){
    myservo.write(0);
  }else{
    myservo.write(100);
  }
*/
}

void SendMessage(){
  //Serial.println ("Sending Message");
  sim.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  //Serial.println ("Set SMS Number");
  sim.println("AT+CMGS=\"" + number + "\"\r"); //Mobile phone number to send message
  delay(1000);
  String SMS = "SPAIRUM 1 Udah mau Habis, isi 4 Galon";
  sim.println(SMS);
  delay(100);
  sim.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  _buffer = _readSerial();
}

String _readSerial() {
  _timeout = 0;
  while  (!sim.available() && _timeout < 12000  )
  {
    delay(13);
    _timeout++;
  }
  if (sim.available()) {
    return sim.readString();
  }
}

void callNumber() {
  sim.print (F("ATD"));
  sim.print (number);
  sim.print (F(";\r\n"));
  _buffer = _readSerial();
  Serial.println(_buffer);
}

void readRFID(){
  rfid.PICC_ReadCardSerial();
  Serial.print("Tag UID: ");
  uidString =String(rfid.uid.uidByte[0]) + " " + String(rfid.uid.uidByte[1]) + " " +
    String(rfid.uid.uidByte[2]) + " " + String(rfid.uid.uidByte[3]);
  Serial.println(uidString);
  delay (1000);
  if (uidString == " 121 135 176 90"){
    myservo.write(0);
    Serial.println("Oke");
    delay(5000);
  }
  if (uidString == " 233 92 68 184"){
  }
  else {
    digitalWrite(pinLed,LOW);
    Serial.println("Akeses di tolak");
    delay(2500);
    digitalWrite(pinLed,HIGH);
   }
}
