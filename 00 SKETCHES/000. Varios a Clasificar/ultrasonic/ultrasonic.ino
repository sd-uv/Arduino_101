/*
HC-SR04 Ping distance sensor]
VCC to arduino 5v GND to arduino GND
Echo to Arduino pin 13 Trig to Arduino pin 12
Red POS to Arduino pin 11
Green POS to Arduino pin 10
Original code improvements to the Ping sketch sourced from Trollmaker.com
Some code and wiring inspired by http://en.wikiversity.org/wiki/User:Dstaub/robotcar
*/
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT22

#define trigPin 13
#define echoPin 12

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  dht.begin();
}

void loop() {
  long duration;
  float distance;
  digitalWrite(trigPin, LOW); // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); // - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  
  
  
//  distance = (duration/2) / 29.1;
  distance = getDistance(duration);

  if (distance >= 200 || distance <= 0){
    Serial.print("Out of range (distance = ");
    Serial.print(distance);
    Serial.print(", duration = ");
    Serial.print(duration);
    Serial.println(")");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(1000);
}


float getDistance(long dur) {
  float t = dht.readTemperature();
  return (dur/2) * ((331.5 + (0.6 * t)) / 10000);
}
