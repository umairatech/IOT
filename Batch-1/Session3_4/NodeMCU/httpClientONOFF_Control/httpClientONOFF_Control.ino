/*
 * Needs ESP8266WiFi, ESP8266HTTPClient Libs
 */
#include<ESP8266WiFi.h>
#include<ESP8266HTTPClient.h>

#define LED D0     

void setup() {
  Serial.begin(9600);
  WiFi.begin("ImranGalaxyNote10", "9886930093");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print('.');
    delay(500);
  }
  Serial.println();
  Serial.println("Connected");
  pinMode(LED, OUTPUT);
}

void loop() {
  HTTPClient http;
  http.begin("http://192.168.43.212:8080/ONOFF");
  int httpStatusCode = http.GET();

  if(httpStatusCode > 0){
    String payload = http.getString();
    String ONSTR = "1";
    String OFFSTR = "0";
    Serial.println(payload);
    if(payload == ONSTR){
      digitalWrite(LED, LOW);
    } 
    else if(payload == OFFSTR){
      digitalWrite(LED, HIGH);
    }
  }
  http.end();

  delay(500);
}
