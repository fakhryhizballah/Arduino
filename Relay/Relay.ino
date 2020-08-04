int LED = 4;
int LED2 = 5;
void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT); 
  pinMode(LED2, OUTPUT); 
  digitalWrite(LED, LOW);
  digitalWrite(LED2, LOW);
  delay(1000); 
  digitalWrite(LED, HIGH);
  digitalWrite(LED2, HIGH);// turn the LED on (HIGH is the voltage level)
   
}

void loop() {
  // put your main code here, to run repeatedly:

}
