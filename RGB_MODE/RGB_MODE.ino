#include <SoftwareSerial.h>
SoftwareSerial mySerial(0, 1);

#define redPin 6
#define greenPin 3
#define bluePin 5
#define whitePin 9

char junk;
String inputString="";



void setup()
{
  // put your setup code here, to run once:

  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(whitePin, OUTPUT);
  analogWrite(redPin, 225);
  delay(2000);
  analogWrite(greenPin, 225);
  analogWrite(redPin, 0);
  delay(2000);
  analogWrite(bluePin, 225);
  analogWrite(greenPin, 0);
  delay(2000);
  analogWrite(whitePin, 225);
  delay(2000);
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
  analogWrite(whitePin, 0);
  delay(2000);
  Serial.println("OKE");
  mySerial.println("OKE");
}

void loop()
{
  // put your main code here, to run repeatedly:

 if(Serial.available()){
  while(Serial.available())
    {
      char inChar = (char)Serial.read(); //read the input
      inputString += inChar;        //make a string of the characters coming on serial
    }
    Serial.println(inputString);
    while (Serial.available() > 0)  
    { junk = Serial.read() ; }      // clear the serial buffer
    if(inputString == "a"){         //in case of 'a' turn the LED on
       fadeRGB();
      Serial.print("fade RGB Mode");
      analogWrite(whitePin, 225);  
      delay(2000);
    }else if(inputString == "b"){   //incase of 'b' turn the LED off
      analogWrite(redPin, 0);
      analogWrite(greenPin, 225);  
      delay(2000);
    }
    inputString = "";
  }

    delay(100);
}

void fadeRGB()
{
  //Red Led

  for (int fadeValue = 0; fadeValue <= 255; fadeValue += 5)
  {
    // sets the value (range from 0 to 255):
    analogWrite(redPin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }
  // fade out from max to min in increments of 5 points:
  for (int fadeValue = 255; fadeValue >= 0; fadeValue -= 5)
  {
    // sets the value (range from 0 to 255):
    analogWrite(redPin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }
  //Green Led
  for (int fadeValue = 0; fadeValue <= 255; fadeValue += 5)
  {
    // sets the value (range from 0 to 255):
    analogWrite(greenPin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }
  // fade out from max to min in increments of 5 points:
  for (int fadeValue = 255; fadeValue >= 0; fadeValue -= 5)
  {
    // sets the value (range from 0 to 255):
    analogWrite(greenPin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }

  //Blue Led
  for (int fadeValue = 0; fadeValue <= 255; fadeValue += 5)
  {
    // sets the value (range from 0 to 255):
    analogWrite(bluePin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }

  // fade out from max to min in increments of 5 points:
  for (int fadeValue = 255; fadeValue >= 0; fadeValue -= 5)
  {
    // sets the value (range from 0 to 255):
    analogWrite(bluePin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }
}
