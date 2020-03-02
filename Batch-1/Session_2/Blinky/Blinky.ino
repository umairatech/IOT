#include<ESP8266WiFi.h>

void setup() {
  Serial.begin(9600);
  pinMode(D0,OUTPUT);
  Serial.println("Started");
}

void loop() {
  digitalWrite(D0,LOW);
  delay(500);
  digitalWrite(D0,HIGH);
  delay(500);
}
