#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C  lcd(0x20 ,2,1,0,4,5,6,7);
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
};

byte rowPins[ROWS] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 22}; //connect to the column pinouts of the keypad

Keypad customKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void setup() {
    Serial.begin(9600);
    lcd.begin(16, 2);          
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Key is: ");
}


void loop() {
  char customKey = customKeypad.getKey();
  
  String z = String(customKey);
  
  if (customKey != NO_KEY){
    //lcd.clear();
    lcd.setCursor(8,0);
   // lcd.print("Key is: ");
    lcd.print(z);
   // Serial.println(customKey);
  }
}  // End loop
