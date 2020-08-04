
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <TelegramBot.h>
#include <WiFiClientSecure.h>

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
/////// Wifi Settings ///////
char ssid[] = "PKSpartaikuPrabowoPresidenku";
char pass[] = "bismillah";

// Initialize Telegram BOT

const char* BotToken = "759895011:AAH9Y8e92K5Xbn6rSKhuQTqcNLHgAkOuyu4";

WiFiSSLClient client;
TelegramBot bot (BotToken,client);

const int ledPin =  6;  // the number of the LED pin


void setup() {

  Serial.begin(115200);
  while (!Serial) {}
  delay(3000);


  // attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");

  bot.begin();
  pinMode(ledPin, OUTPUT);

}

void loop() {

  message m = bot.getUpdates(); // Read new messages

  if ( m.text.equals("On")) {
    digitalWrite(ledPin, HIGH);
    Serial.println("message received");
    bot.sendMessage(m.chat_id, "The Led is now ON");
  }
  else if ( m.text.equals("Off")) {
    digitalWrite(ledPin, LOW);
    Serial.println("message received");
    bot.sendMessage(m.chat_id, "The Led is now OFF");
  }
}
