#include<ESP8266WiFi.h>
#include<ESP8266WebServer.h>

ESP8266WebServer server;

void setup() {
  Serial.begin(9600);
  WiFi.begin("ImranGalaxyNote10","9886930093");
  pinMode(D0,OUTPUT);
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println(WiFi.localIP());
  server.on("/", sendMessage);
  server.on("/ledON",ledon);
  server.on("/ledOFF",ledoff);
  server.on("/ledtoggle",ledtoggle);
  server.begin();
}

void loop() {
  server.handleClient();
}

void sendMessage(){
 server.send(200,"text/plain","HELLO");
}

void ledon()
{
  digitalWrite(D0,LOW);
  server.send(200,"text/plain","LED ON FUNCTION");
}

void ledoff()
{
  digitalWrite(D0,HIGH);
  server.send(200,"text/plain","LED OFF FUNCTION");
}
void ledtoggle()
{
  server.send(204,"text/plain");
  for(int i=0;i<10;i++){
    digitalWrite(D0,LOW);
    delay(500); 
    digitalWrite(D0,HIGH);
    delay(500);
  }
}
