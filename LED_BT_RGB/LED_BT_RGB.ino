#include <SoftwareSerial.h>
SoftwareSerial mySerial(0, 1); //Pin10 RX , Pin 11 TX connected to--> Bluetooth TX,RX

#define relay1 6
#define relay2 3
#define relay3 5
#define relay4 9

int val;
void setup() {
pinMode(relay1,OUTPUT);
pinMode(relay2,OUTPUT);
pinMode(relay3,OUTPUT);
pinMode(relay4,OUTPUT);
digitalWrite(relay1,LOW);
digitalWrite(relay2,LOW);
digitalWrite(relay3,LOW);
digitalWrite(relay4,HIGH);
mySerial.begin(9600);
Serial.begin(9600);
Serial.println("lest");
}

void loop() {
//cek data serial from bluetooth android App
if( mySerial.available() >0 ) {
val = mySerial.read();
Serial.println(val);
}
//Relay is on
if( val == 'r' ) {
analogWrite(relay1,LOW);}
else if( val == 'g' ) {
digitalWrite(relay2,LOW); }
else if( val == 'b' ) {
digitalWrite(relay3,LOW); }
else if( val == 'w' ) {
digitalWrite(relay4,LOW); }
//relay all on
else if( val == 'o' ) {
digitalWrite(relay1,LOW);
digitalWrite(relay2,LOW);
digitalWrite(relay3,LOW);
digitalWrite(relay4,LOW);
}
//relay is oN
else if( val == 'R' ) {
digitalWrite(relay1,HIGH);
Serial.println("OFF");}
else if( val == 'G' ) {
digitalWrite(relay2,HIGH); }
else if( val == 'B' ) {
digitalWrite(relay3,HIGH); }
else if( val == 'W' ) {
digitalWrite(relay4,HIGH); }
//relay all off
else if( val == 'O' ) {
digitalWrite(relay1,HIGH);
digitalWrite(relay2,HIGH);
digitalWrite(relay3,HIGH);
digitalWrite(relay4,HIGH); }
else if( val == 'D' ) {
  analogWrite(relay3, 76);}
}
