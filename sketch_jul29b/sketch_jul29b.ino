#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         4          // Configurable, see typical pin layout above
#define SS_PIN          5         // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
int count = 0;

  
void setup() 
{
  Serial.print("RFID attendance");

//servo1.write(0,60,true);
 
Serial.begin(9600);    // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
  Serial.println("Put your card to the reader...");
  Serial.println();

}
void loop() 
{
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
    delay(500);
    count++;                    // Increment Count by 1
    Serial.print("Fakhry Hizballah");
    Serial.print(count);
    delay(400);
  }
   if (content.substring(1) == "6A 22 5D 74") 
  {
    Serial.println("Authorized access");
    Serial.println();
    count++;  // Increment Count by 1
      Serial.print("VC Sir is Present");
    Serial.print(count);
    delay(400);
  }

 else   {
    Serial.println(" Access denied");
  }
  {
    return;
  }
} 
