int flowPin = 2;
double flowRate;
volatile int count;
unsigned long oldTime;
 
 
void setup() {
 
  Serial.begin(115200);
  pinMode(flowPin, INPUT);
  attachInterrupt(0,flow,FALLING);
}
 
void loop() {
   
  if (millis() - oldTime > 10){ // baca sinyal pulse setiap 10 milli second
    detachInterrupt(0);   // non aktifkan interuptsi
    Serial.println(count); // // tampilakan jumla counter sinyal output water flow
     
    oldTime = millis(); // update waktu internal
    //count = 0;
    attachInterrupt(0,flow,FALLING); // aktifkan lagi interruptsi
  }  
}
 
void flow(){
  count++; // counter jika ada sinyal FALLING di pin 2 ( int0 )
}
