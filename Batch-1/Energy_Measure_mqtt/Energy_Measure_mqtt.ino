/*
 Basic ESP8266 MQTT example

 This sketch demonstrates the capabilities of the pubsub library in combination
 with the ESP8266 board/library.

 It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic" every two seconds
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
  - If the first character of the topic "inTopic" is an 1, switch ON the ESP Led,
    else switch it off

 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.

 To install the ESP8266 board, (using Arduino 1.6.4+):
  - Add the following 3rd party board manager under "File -> Preferences -> Additional Boards Manager URLs":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Open the "Tools -> Board -> Board Manager" and click install for the ESP8266"
  - Select your ESP8266 in "Tools -> Board"

*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.

#define LED_BUILTIN 2
#define RELAY_PIN D2

const char* ssid = "Imran";
const char* password = "9886930093";
//const char* ssid = "ACT-WAN";
//const char* password = "WAN@XYID@2016";
const char* mqtt_server = "umairatech.com";
float wh;
float power;
int current;
long current_time;
long last_time;
long time_elapsed;
const float sensitivity = 0.02325;
float actual_current;
const int supply_voltage = 230;
const int pf = 85;

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
char rcvMsg[50];
int value = 0;
uint8_t mac[6];
char macString[30];
char buildMessage[50];

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.macAddress(mac);
  WiFi.begin(ssid, password);
  memset(macString,'\0',sizeof(macString));
  sprintf(macString,"%d%d%d%d%d%d", mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]); 
  Serial.println(macString);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    rcvMsg[i] = (char)payload[i];
    Serial.print((char)payload[i]);
  }
  Serial.println();


  if(strstr(rcvMsg,"&101=1"))
  {
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(RELAY_PIN, HIGH);
    memset(rcvMsg,'\0', sizeof(rcvMsg));
    sprintf(buildMessage,"{\"id\":%s,\"command\":1011}", macString);  
    client.publish("device2server/command", buildMessage);
    //sprintf(buildMessage,"%s,%s", macString,"&101=1*");
    //client.publish("device2server/command", buildMessage);
  }
  else if(strstr(rcvMsg,"&101=0"))
  {
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(RELAY_PIN, LOW);
    memset(rcvMsg,'\0', sizeof(rcvMsg));
    sprintf(buildMessage,"{\"id\":%s,\"command\":1010}", macString);  
    client.publish("device2server/command", buildMessage);
    wh = 0.0;
    //sprintf(buildMessage,"%s,%s", macString,"&101=0*");
    //client.publish("device2server/command", buildMessage);
  }
  else
  {
    memset(rcvMsg,'\0', sizeof(rcvMsg));
  }
  
//  if ((char)payload[0] == '1') {
//    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
//  } else {
//    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
//  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
    sprintf(buildMessage,"{\"id\":%s,\"command\":1000}", macString);  
    client.publish("device2server/command", buildMessage);
    
     //// client.publish("device2server/command", "8266123456789");
      // ... and resubscribe

      sprintf(buildMessage, "server2device/%s", macString);
      client.subscribe(buildMessage);
      
      //client.subscribe("server2device/8266123456789");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the BUILTIN_LED pin as an output 
  digitalWrite(LED_BUILTIN, HIGH);
  pinMode(RELAY_PIN, OUTPUT);     
  digitalWrite(RELAY_PIN, LOW);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  last_time = current_time;
  long now = millis();
  if (now - lastMsg > 5000) {
    current_time = millis();
    time_elapsed = current_time - last_time;
    Serial.println(time_elapsed);
    lastMsg = now;
    ++value;
    current = analogRead(A0);
    Serial.println(current);
    if(current < 3)
    {
      current = 0;  
    }
    actual_current = sensitivity * current;
    power = (supply_voltage * actual_current) * (pf / 100.0);
    wh = power * (time_elapsed / 3600000.0);
    //wh = wh + power * (time_elapsed / 3600000.0);
    
    
    sprintf(buildMessage,"{\"id\":%s,\"wh\":%0.3f}", macString,wh);  
    client.publish("device2server/command", buildMessage);
    Serial.print("Publish message: ");
    Serial.println(buildMessage);
    //client.publish("device2server/command", "8266123456789");
  }
}
