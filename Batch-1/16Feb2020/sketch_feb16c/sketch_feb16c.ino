#include<ESP8266WiFi.h>
#include<ESP8266WebServer.h>

ESP8266WebServer server;

void setup() {
  pinMode(D0,OUTPUT);
  Serial.begin(9600);
  WiFi.begin("ImranGalaxyNote10","9886930093");

  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("IP address:");
  Serial.println(WiFi.localIP());
  server.on("/", sendResponse);
  server.on("/toggle",toggleLED);
  server.begin();
}

void loop() {
  server.handleClient();

}

void sendResponse()
{
  server.send(200,"text/plain","Hello ESP");
}
void toggleLED()
{
  digitalWrite(D0,!digitalRead(D0));
  if(digitalRead(D0))
  {
    server.send(200,"text/plain","LED ON");
    Serial.println("First");
    Serial.println(digitalRead(D0));
  }
  else
  {
    server.send(200,"text/plain","LED OFF");
    Serial.println("Second");
    Serial.println(digitalRead(D0));
  }
  
}
