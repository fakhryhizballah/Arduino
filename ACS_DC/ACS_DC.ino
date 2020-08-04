void setup() {

Serial.begin(9600);
}

void loop() {
float average = 0;
for(int i = 0; i<= 1000; i++) { // sample 1000 times by 1 ms
        average = average + (.0264 * analogRead(A0) -13.51);
        delay(1);
}
Serial.print(average);
Serial.println("mA");

}
