#include <SoftwareSerial.h>
SoftwareSerial belutut(10, 11); // RX | TX
void setup() {
    Serial.begin(9600);
    Serial.println("Masukkan perintah AT:");
    belutut.begin(38400); //Baudrate
}
void loop() {
    //Membaca dari HC05 dan di Print pada serial Monitor
    if (belutut.available())
    Serial.write(belutut.read());
    //Membaca dari Arduino Serial monitor untuk dikirim ke HC05
    if (Serial.available())
    belutut.write(Serial.read());
}
