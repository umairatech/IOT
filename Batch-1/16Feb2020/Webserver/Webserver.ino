#include<ESP8266WiFi.h>
#include<ESP8266WebServer.h>

ESP8266WebServer server;

void setup() {
  Serial.begin(9600);
  WiFi.begin("ImranGalaxyNote10","9886930093");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println(WiFi.localIP());
  server.on("/", sendMessage);
  server.on("/ledtoggle",ledtoggle);
  server.begin();
}

void loop() {
  server.handleClient();
}

void sendMessage(){
 server.send(200,"text/plain","HELLO");
}

void ledtoggle()
{
  server.send(200,"text/plain","LED FUNCTION");
}
