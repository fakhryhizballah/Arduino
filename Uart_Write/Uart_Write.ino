#include<SoftwareSerial.h> //Included SoftwareSerial Library
//Started SoftwareSerial at RX and TX pin of ESP8266/NodeMCU
SoftwareSerial s(3,1);
int data;

void setup() {
  //Serial S Begin at 9600 Baud
  s.begin(115200);
  //Serial.begin(115200);
}

void loop() {
  //Write '123' to Serial
  //s.write(123);
  delay(1000);
  data = s.read();
  s.println(data);
}
