#include<SoftwareSerial.h>
SoftwareSerial trans(2, 3); //RX and TX pin
int data; //Initialized variable to store recieved data

void setup() {
  //Serial Begin at 9600 Baud 
  Serial.begin(9600);
  trans.begin(115200);
}

void loop() {
  //data = trans.read(); //Read the serial data and store it
  delay(1000);
  //Serial.println(data);
  trans.write(221);
}
