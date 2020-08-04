#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); //Pin10 RX , Pin 11 TX connected to--> Bluetooth TX,RX
char Incoming_value = 0;
int state = 0;


int val;
void setup() {
  // put your setup code here, to run once:
mySerial.begin(9600);
Serial.begin(9600);
pinMode(9, OUTPUT);
}

void loop() {
   if(Serial.available() > 0)  
  {
    Incoming_value = mySerial.read();      //Read the incoming data and store it into variable Incoming_value
    Serial.print(Incoming_value);        //Print Value of Incoming_value in Serial monitor
    Serial.print("\n");        //New line 
    if(Incoming_value == '1')            //Checks whether value of Incoming_value is equal to 1 
      digitalWrite(9, HIGH);  //If value is 1 then LED turns ON
    else if(Incoming_value == '2')       //Checks whether value of Incoming_value is equal to 0
      digitalWrite(9, LOW);   //If value is 0 then LED turns OFF
  }                        
}
