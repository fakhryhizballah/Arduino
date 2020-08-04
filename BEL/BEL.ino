int BTN1 =2;
int BTN2 =3;
int BTN3 =4;
int BTN4 =5;
int BTN5 =6;
int Val1 =0;
int Val2 =0;
int Val3 =0;
int Val4 =0;
int Val5 =0;
int BEL1 =7;
int BEL2 =8;
int BEL3 =9;
int BEL4 =10;
int BEL5 =11;
void setup() {
  pinMode(BTN1, INPUT);
  pinMode(BTN2, INPUT);
  pinMode(BTN3, INPUT);
  pinMode(BTN4, INPUT);
  pinMode(BTN5, INPUT);
  pinMode(BEL1, OUTPUT);
  pinMode(BEL2, OUTPUT);
  pinMode(BEL3, OUTPUT);
  pinMode(BEL4, OUTPUT);
  pinMode(BEL5, OUTPUT);

}

void loop() {
  Val1 = digitalRead(BTN1);
  Val2 = digitalRead(BTN2);
  Val3 = digitalRead(BTN3);
  Val4 = digitalRead(BTN4);
  Val5 = digitalRead(BTN5);
  if (Val1 == LOW) {
    digitalWrite(BEL1, HIGH);
    digitalWrite(BEL2, LOW);
    digitalWrite(BEL3, LOW);
    digitalWrite(BEL4, LOW);
    digitalWrite(BEL5, LOW);
    return;
    } 
    if (Val2 == LOW) {
    digitalWrite(BEL1, LOW);
    digitalWrite(BEL2, HIGH);
    return;
    } else if (Val3 == LOW) {
    digitalWrite(BEL3, HIGH);
    }else if (Val4 == LOW) {
    digitalWrite(BEL4, HIGH);
    }else if (Val5 == LOW) {
    digitalWrite(BEL5, HIGH);
    }
    digitalWrite(BEL1, LOW);
    digitalWrite(BEL2, LOW);
    digitalWrite(BEL3, LOW);
    digitalWrite(BEL4, LOW);
    digitalWrite(BEL5, LOW);
}
