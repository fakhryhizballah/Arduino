#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C  lcd(0x20 ,2,1,0,4,5,6,7);
#include <Keypad.h>

#define Length 10

int ResetPin = 22;
int Reset = 0;
 
char Data[Length]; 
byte data_count = 0;
char customKey;
char nominal;

int Oke = 0;

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
};

byte rowPins[ROWS] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 8}; //connect to the column pinouts of the keypad

Keypad customKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);          
  lcd.backlight();
  lcd.clear();
  pinMode(ResetPin, INPUT);
}

void Nominal(){
 
}

void loop() {

  Reset = digitalRead(ResetPin);
  if (Reset == LOW){
    Serial.print("OK");
    delay(1000);
  }
     customKey = customKeypad.getKey();
  if (customKey){
    Data[data_count] = customKey; 
    lcd.setCursor(data_count,1); 
    lcd.print(Data[data_count]);
    data_count++; 
    }
  if (customKey  == '#'){
    Serial.println(Data);
    data_count = 0;
    Data[data_count] = 0;
    Serial.println(Data);
    lcd.clear();
  }
  delay (100);
}
