#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C  lcd(0x3f ,2,1,0,4,5,6,7);

#include <SPI.h> // library RFID and SD card module
#include <SD.h> // library SD card module
#define SS_SD 4 // SS SD Card

File dataFile;

#include <MFRC522.h> // library RFID
#define RST_PIN 5
#define SS_PIN 53 //MFRC522 pin
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

#include <RTClib.h>
#include "RTClib.h"
RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"}; //prosedur pembacaan I2C

const int  motorPompa = 7; // Tidak di gunakan lagi
const int  buttonOke = 6; // Tombol stop
const int  buttonIsi = 22; //Tombol

int Oke = 0;
int Isi = 0;
int count = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  pinMode(motorPompa,OUTPUT);
  pinMode(buttonOke,INPUT);

  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("Kredit Air");
  delay(1000);
  lcd.clear();

  // Setup for the RTC  
  if(!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    lcd.clear();
    lcd.print("Couldn't find RTC");
    while(1);
  }
  else {
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

 if (! rtc.isrunning()) {
  Serial.println("RTC is NOT running!");
  }
      // following line sets the RTC to the date & time this sketch was compiled
      //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
      // This line sets the RTC with an explicit date & time, for example to set
      // January 21, 2014 at 3am you would call:
      //rtc.adjust(DateTime(2019, 5, 22, 15, 26, 37));
   };

  Serial.print("Initializing SD card...");
  if (!SD.begin(SS_SD)) {
    Serial.println("initialization failed!");
    lcd.setCursor(0,0);
    lcd.print("initialization failed! Periksa Memory Card");
    lcd.setCursor(0,2);
    lcd.print("......................  Silakan Reset ");
    for (int positionCounter = 0; positionCounter < 22; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft();
    // wait a bit:
    delay(150);
    }
    //while (1);
  }
  Serial.println("initialization done.");
  delay(2000);
   SPI.begin();      // Init SPI bus
   mfrc522.PCD_Init();   // Init MFRC522
   mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
   Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
   Serial.println("Put your card to the reader...");
   Serial.println();
}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("TAP KARTU");
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  // Dump debug info about the card; PICC_HaltA() is automatically called
  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid)); 

  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();

  if (content.substring(1) == "68 52 FF 29")
  {
    Serial.println("Authorized access");
    Serial.println();
    Serial.print("Fakhry Hizballah");
    lcd.setCursor(0,0);
    lcd.print("Akeses diterima");
    lcd.setCursor(0,1);
    lcd.print("Fakhry");
//    printRTC();
    dataFile = SD.open("Water.txt", FILE_WRITE);
    if (dataFile){
      dataFile.print("Fakhry");
      dataFile.print(' ');
      Serial.print("Done");
      dataFile.close();
    } else {
      Serial.println(" error opening Water.txt");
      lcd.clear();
      lcd.setCursor(0,2);
      lcd.print("Gagal di Save");
    }
    delay(1500);

    Chager();
    Serial.println("Done");
    delay(400);
  }
   if (content.substring(1) == "6A 22 5D 74")
  {
    Serial.println("Authorized access");
    Serial.println();
      Serial.print("VC Sir is Present");
      lcd.setCursor(0,0);
      lcd.print("Akeses diterima");
      Chager();
    delay(400);
  }

 else   {
  lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Akeses ditolak");
    Serial.println(" Access denied");
    delay(2500);
    lcd.clear();
  }
  {
    return;
  }

  //Pompa = digitalRead(buttonPompa);
  //lcd.setCursor(0,0);
  //lcd.print("Klik Pompa");
  //if (Pompa == LOW){
  //Chager();
    //Serial.print("Off");
  //}

}

void Chager() {
  Serial.println();
  Serial.println("Rady");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Tekan Tombol Isi");
  delay(2000);
  lcd.clear();
  int var = 0;
  while (var < 100) {
   Isi = digitalRead(buttonIsi);
  if (Isi == LOW){
    //digitalWrite(motorPompa, HIGH);
    count++;
  var++;
  Serial.print(count);
  delay (100);
  }
  //digitalWrite(motorPompa, LOW);
  lcd.setCursor(0,0);
  lcd.print(count);
  lcd.print("mL");
  delay(250);
  if (var == 100){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Ups Maksimum");
    lcd.setCursor(0,2);
    lcd.print(count);
    lcd.print("mL");
    delay(2500);
  }
  Oke = digitalRead(buttonOke);
  if (Oke == LOW){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Selesai Mengisi");
    delay(1000);
    var = 100;
    lcd.clear();
    }
  }
  lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Selesai Mengisi");
    delay(1000);
    lcd.clear();
  dataFile = SD.open("Water.txt", FILE_WRITE);
    if (dataFile) {
    Serial.print(count);
    dataFile.print(count);
    dataFile.print(' ');
    dataFile.println("mL");
    dataFile.close();
    Serial.println("done.");
    lcd.setCursor(0,0);
    lcd.print("SAVE");
    lcd.setCursor(0,2);
    lcd.print(count);
    lcd.print("mL");
    delay(3500);
    } else {
      Serial.println(" error opening Water.txt");
      lcd.clear();
      lcd.setCursor(0,2);
      lcd.print("Gagal di Save");
    }
    Serial.print("Resst");
    count=0;
    lcd.clear();
}

//void printRTC() {
//  DateTime now = rtc.now();
//  dataFile = SD.open("Water.txt", FILE_WRITE); //Membuka File datalogger.txt
//  if (dataFile) // jika file tersedia tulis data
//  {dataFile.print(now.day(), DEC);
 //      dataFile.print('/');
 //      dataFile.print(now.month(), DEC);
 //      dataFile.print('/');
 //      dataFile.print(now.year(), DEC);
 //      dataFile.print(" , ");
 //      dataFile.print(now.hour(), DEC);
 //      dataFile.print(':');
 //      dataFile.print(now.minute(), DEC);
 //      dataFile.print(':');
 //      dataFile.print(now.second(), DEC);
 //      dataFile.print(" , ");

  // dataFile.close();
  //   Serial.println("done.");
 //      lcd.setCursor(15,0);
 //      lcd.print("OKE Asiyap");
//  }
//  else
//  {
//  Serial.println("Failed open datalogger.txt"); // jika gagal print error
//  lcd.setCursor(15,0);
//  lcd.print("Faill");
//  }
//}
