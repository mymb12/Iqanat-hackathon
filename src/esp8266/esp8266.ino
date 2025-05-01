#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Wi-FI";
const char* password = "01011966";
const char* serverName = "http://192.168.0.25:11223/data";

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }

  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    String line = Serial.readStringUntil('\n');
    float distance, temp;
    int water;

    sscanf(line.c_str(), "%f,%d,%f", &distance, &water, &temp);

    WiFiClient client;
    HTTPClient http;

    http.begin(client, serverName);

    http.addHeader("Content-Type", "application/json");

    String json = "{\"distance\":" + String(distance) +
                  ",\"water\":" + String(water) + 
                  ",\"temp\":" + String(temp)+ "}";
    int httpResponseCode = http.POST(json);

    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);

    http.end();
  } else {
    Serial.print("Failed connecting to WiFi: ");
    Serial.println(ssid);
  }

  delay(5000);
}
