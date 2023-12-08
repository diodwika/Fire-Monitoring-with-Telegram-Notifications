#include <WiFi.h>
#include <HTTPClient.h>

// Define your Telegram bot token and chat ID
#define TELEGRAM_BOT_TOKEN "6772737185:AAGGdUgjR80nUHy6N_vLDbpGLvv0xzcXdO8"
#define TELEGRAM_CHAT_ID "1916454355"

#define flamePin 14

const char *ssid = "HOTEL KING AULA";
const char *password = "2+2+2+2+2+2+2+2";
const char *receiverIP = "192.168.1.32"; // Ganti dengan alamat IP ESP32 receiver
const int receiverPort = 80; // Sesuaikan dengan port server pada receiver

void sendTelegramNotification(String message) {
  HTTPClient http;
  String url = "https://api.telegram.org/bot" + String(TELEGRAM_BOT_TOKEN) +
               "/sendMessage?chat_id=" + String(TELEGRAM_CHAT_ID) +
               "&text=" + message;

  http.begin(url);

  int httpResponseCode = http.GET();
  if (httpResponseCode > 0) {
    Serial.print("Telegram notification sent successfully. Response code: ");
    Serial.println(httpResponseCode);
  } else {
    Serial.print("Error sending Telegram notification. Response code: ");
    Serial.println(httpResponseCode);
  }

  http.end();
}

void setup() {
  pinMode(flamePin, INPUT);
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
}

void loop() {
  bool fireStatus = digitalRead(flamePin);
  // Terhubungkan ke receiver
  WiFiClient client;
  if (client.connect(receiverIP, receiverPort)) {
    // Kirim data ke receiver
    if(fireStatus == true){
      client.println("ADA API!!!");
      client.stop();
      Serial.print("APIIIII");
      Serial.println();
      sendTelegramNotification("AAAAAAAaAAAAAAA");
    }
    else{
      client.println("AMAN BANG!!!");
      client.stop();
      Serial.print("AMAN ATUH BANG!!!");
      Serial.println();
    }
  }
  delay(500); // Tunggu 5 detik sebelum mengirim lagi
}
