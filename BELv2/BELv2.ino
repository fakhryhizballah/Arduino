const int tombolA = 2;
const int tombolB = 3;
const int tombolC = 4;
const int tombolD = 5;
const int tombolE = 6;
const int lampuA = 7;
const int lampuB = 8;
const int lampuC = 9;
const int lampuD = 10;
const int lampuE = 11;
const int bel = 12;
void setup(){
for(char i=2; i<8; i++){
pinMode(i, INPUT);
digitalWrite(i,HIGH);
}
for(char i=7; i<12; i++){
pinMode(i, OUTPUT);
digitalWrite(i,LOW);
}
}
void loop(){
if(digitalRead(tombolA)==LOW){
digitalWrite(bel,HIGH);
digitalWrite(lampuA,HIGH);
delay(500);
while(!digitalRead(tombolA));
digitalWrite(bel,LOW);
digitalWrite(lampuA,LOW);
}
else if(digitalRead(tombolB)==LOW){
digitalWrite(bel,HIGH);
digitalWrite(lampuB,HIGH);
delay(500);
while(!digitalRead(tombolB));
digitalWrite(bel,LOW);
digitalWrite(lampuB,LOW);
}
else if(digitalRead(tombolC)==LOW){
digitalWrite(bel,HIGH);
digitalWrite(lampuC,HIGH);
delay(500);
while(!digitalRead(tombolC));
digitalWrite(bel,LOW);
digitalWrite(lampuC,LOW);
}
else if(digitalRead(tombolD)==LOW){
digitalWrite(bel,HIGH);
digitalWrite(lampuD,HIGH);
delay(500);
while(!digitalRead(tombolD));
digitalWrite(bel,LOW);
digitalWrite(lampuD,LOW);
}
else if(digitalRead(tombolE)==LOW){
digitalWrite(bel,HIGH);
digitalWrite(lampuE,HIGH);
delay(500);
while(!digitalRead(tombolE));
digitalWrite(bel,LOW);
digitalWrite(lampuE,LOW);
}
}
