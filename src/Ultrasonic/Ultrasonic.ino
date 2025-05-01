#include "DHT.h"
#include <Ultrasonic.h>

#define trigPin 12
#define echoPin 13
#define ledPin 6
#define DHTTYPE DHT11
#define DHTPin 7

//DHT dht(DHTPin, DHTTYPE);
Ultrasonic ultrasonic(trigPin, echoPin);
int distance;

int waterSensorPin = A0;

void setup() {
  Serial.begin(9600);
  //Serial.println(F("DHTxx test!"));

  pinMode(ledPin, OUTPUT);

  //dht.begin();
}

void loop() {
  delay(500);
  
  // Distance
  distance = ultrasonic.read();
  
  if(distance < 5) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
  
  // Water level
  int sensorValue = analogRead(waterSensorPin);

  
  if(distance < 5) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
  

  // Temperature
  //float t = dht.readTemperature();
  float t = 24.0;

  Serial.print(distance);
  Serial.print(",");
  Serial.print(sensorValue);
  Serial.print(",");
  Serial.println(t);
}
