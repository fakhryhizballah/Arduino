#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

char ssid[] = "PKSpartaikuPrabowoPresidenku"; 
char password[] = "bismillah";
#define BOTtoken "759895011:AAH9Y8e92K5Xbn6rSKhuQTqcNLHgAkOuyu4"
String chatid = "542485419";

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

void setup() {
  Serial.begin(9600);
  WifiStatus();

  bot.sendMessage(chatid, "Esp Tersambung");
  Serial.println("Pesan Terkirim ke Telegram");
}

void loop() {

}

void WifiStatus() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
