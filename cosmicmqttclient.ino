#include <ESP8266WiFi.h>
#include <PubSubClient.h>
//#include <ArduinoJson.h>
 
const char* ssid = "Ridwan"; // Enter your WiFi name
const char* password =  "ridwanamsha"; // Enter WiFi password
const char* mqttServer = "192.168.43.110";
const int mqttPort = 1883;

int randNumber;
//const char* mqttUser = "otfxknod";
//const char* mqttPassword = "nSuUc1dDLygF";
 
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup() {
 
  Serial.begin(115200);
  randomSeed(analogRead(0));
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266Client")) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
 
 
}
 
void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
 
  Serial.println();
  Serial.println("-----------------------");
 
}
 
void loop() {
//  client.loop();
randNumber = random(50);
Serial.println(randNumber);
delay(1000);
 String misal;
 misal = "{\"operation\": 1,\"input\": {\"tem\": "+String(randNumber)+",\"hum\": 100,\"volt\":220},\"output\": {\"fan\": true}}";
 char finalDataChar[misal.length() + 1];
//    char topicChar[topic.length() + 1];

    misal.toCharArray(finalDataChar, misal.length() + 1);
//    topic.toCharArray(topicChar, topic.length() + 1);

  client.publish("api/v1/req/app/smarthome/dev/sensor-123", finalDataChar); //Topic name
  client.subscribe("esp/test");
}
