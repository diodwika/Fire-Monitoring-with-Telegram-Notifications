#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>

int buzzerPin = 5;  // Sesuaikan dengan pin buzzer Anda

WiFiServer server(80);
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Sesuaikan alamat I2C dengan LCD Anda

const char *ssid = "HOTEL KING AULA";
const char *password = "2+2+2+2+2+2+2+2";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.begin();

  // Initialize the LCD
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  lcd.print("WiFi Connected");

  // Initialize the buzzer pin
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);  // Turn off buzzer initially
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("Client connected");

    while (client.connected()) {
      if (client.available()) {
        String data = client.readStringUntil('\n');
        Serial.println("Data diterima: " + data);

        // Display data on LCD
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Data: ");
        lcd.setCursor(0, 1);
        lcd.print(data);

        // Check if the received data is "ADA API!!!"
        if (data.indexOf("ADA API!!!") != -1) {
          // If "ADA API!!!" is found, turn on the buzzer
          digitalWrite(buzzerPin, HIGH);
          delay(500); // Buzzer on for 1 second (adjust as needed)
          digitalWrite(buzzerPin, LOW); // Turn off the buzzer
        }

        // Process data as needed
      }
    }
  }
}
