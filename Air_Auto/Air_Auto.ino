const int btnUp = 5;
const int btnMid = 4;
const int btnDown = 3;
const int Motor = 2;
int sensor1 = 0;
int sensor2 = 0;
int sensor3 = 0;
int val = 0;
int Waiting =0;

void setup() {
  Serial.begin(9600);
  pinMode(btnUp, INPUT);
  pinMode(btnMid, INPUT);
  pinMode(btnDown, INPUT);
  pinMode(Motor, OUTPUT);
  digitalWrite(Motor, HIGH);
}

void loop() {
  sensor1 = digitalRead(btnUp);
  sensor2 = digitalRead(btnMid);
  sensor3 = digitalRead(btnDown);
  // Jika pelampung OFF
  if (sensor1==LOW){
    val = 100;
  }else if (sensor2==LOW){
    val = 75;
  }else if (sensor3==LOW){
    val = 50;
  }else {
    val = 25;
  }
  Serial.println(val);
  if (val == 25){
    digitalWrite(Motor, LOW);
    Waiting = 100;
  }
  if (Waiting == 100){
    Serial.print("OK");
    if (val==100){
      digitalWrite(Motor, HIGH);
      Waiting=0;
    }
  }
} 
