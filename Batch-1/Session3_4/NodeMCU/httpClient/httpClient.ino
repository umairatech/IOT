/*
 * Needs ESP8266WiFi, ESP8266HTTPClient Libs
 */
#include<ESP8266WiFi.h>
#include<ESP8266HTTPClient.h>

void setup() {
  Serial.begin(9600);
  WiFi.begin("ImranGalaxyNote10", "9886930093");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print('.');
    delay(500);
  }
  Serial.println();
  Serial.println("Connected");
}

void loop() {
  HTTPClient http;
  http.begin("http://192.168.43.212:8080/Welcome");
  int httpStatusCode = http.GET();

  if(httpStatusCode > 0){
    String payload = http.getString();
    Serial.println(payload);
    Serial.println(httpStatusCode);
  }
  http.end();

  delay(1000);
}
