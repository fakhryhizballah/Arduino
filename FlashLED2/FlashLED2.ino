/*******************************************************************
 *  An example of bot that receives commands and turns on and off  *
 *  an LED.                                                        *
 *                                                                 *
 *  written by Giacarlo Bacchio (Gianbacchio on Github)            *
 *  adapted by Brian Lough                                         *
 *******************************************************************/
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

// Initialize Wifi connection to the router
char ssid[] = "Azimi";     // your network SSID (name)
char password[] = "bismillah"; // your network key

// Initialize Telegram BOT
#define BOTtoken "759895011:AAEwtLkxf5LLo-27HG84mwDN61ufabi_WQY"  // your Bot Token (Get from Botfather)

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int Bot_mtbs = 1000; //mean time between scan messages
long Bot_lasttime;   //last time messages' scan has been done
bool Start = false;

const int ledPin1 = 13;
const int ledPin2 = 11;
int ledStatus = 0;

void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "") from_name = "Guest";

    if (text == "/led1on") {
      digitalWrite(ledPin1, HIGH);   // turn the LED on (HIGH is the voltage level)
      ledStatus = 1;
      bot.sendMessage(chat_id, "Led 1 is ON", "");
    }

    if (text == "/led1off") {
      ledStatus = 0;
      digitalWrite(ledPin1, LOW);    // turn the LED off (LOW is the voltage level)
      bot.sendMessage(chat_id, "Led 1 is OFF", "");
    }
        if (text == "/ledon") {
      digitalWrite(ledPin2, HIGH);   // turn the LED on (HIGH is the voltage level)
      ledStatus = 2;
      bot.sendMessage(chat_id, "Led 2 is ON", "");
    }

    if (text == "/led2off") {
      ledStatus = 3;
      digitalWrite(ledPin2, LOW);    // turn the LED off (LOW is the voltage level)
      bot.sendMessage(chat_id, "Led 2 is OFF", "");
    }

    if (text == "/status") {
      if(ledStatus){
        bot.sendMessage(chat_id, "Led is ON", "");
      } else {
        bot.sendMessage(chat_id, "Led is OFF", "");
      }
    }

    if (text == "/start") {
      String welcome = "LKTI Arduino Telegram Bot , " + from_name + ".\n";
      welcome += "Contoh perintah.\n\n";
      welcome += "/led1on : Untuk menghidupkan LED 1\n";
      welcome += "/led1off : Untuk mematiakn LED 1\n";
      welcome += "/led2on : Untuk menghidupkan LED 2\n";
      welcome += "/led2off : Untuk mematiakn LED 2\n";
      welcome += "/status : Untuk melihat status LED\n";
      bot.sendMessage(chat_id, welcome, "Markdown");
    }
  }
}


void setup() {
  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // attempt to connect to Wifi network:
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

  pinMode(ledPin1, OUTPUT); // initialize digital ledPin as an output.
  pinMode(ledPin2, OUTPUT);
  delay(10);
  digitalWrite(ledPin1, LOW); // initialize pin as off
}

void loop() {
  if (millis() > Bot_lasttime + Bot_mtbs)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    Bot_lasttime = millis();
  }
}
