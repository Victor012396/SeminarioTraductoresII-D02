#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SPI.h>
#define Photoresistor A0
int var;
String resultS;
// WiFi
const char *ssid = "dlink-D82C"; // Enter your WiFi name
const char *password = "qpmws68912";  // Enter WiFi password

// MQTT Broker
const char *mqtt_broker = "192.168.0.101";
const char *topic = "esp8266/test";
const char *mqtt_username = "admin";
const char *mqtt_password = "public";
const int mqtt_port = 1883;
//int sensor=0;
//char datos[40];



WiFiClient espClient;
PubSubClient client(espClient);
void startWifi(){
  // connecting to a WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");

}



void setup() {
  // Set software serial baud to 115200;
  pinMode(2,OUTPUT);
  Serial.begin(9600);

  
  startWifi();
  //connecting to a mqtt broker
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
   if(!client.connected()) {
    reconnect();
  }
  
}
void reconnect() {
  while (!client.connected()) {
      String client_id = "esp8266-client";
      client_id += String(WiFi.macAddress());
      Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
      if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
          Serial.println("Public emqx mqtt broker connected");
      } else {
          Serial.print("failed with state ");
          Serial.print(client.state());
          delay(2000);
      }
  }
  // publish and subscribe
  client.publish(topic, "hello emqx");
  client.subscribe(topic);
  //client.subscribe("esp8266/led");

}
void callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  char payload_string[length + 1];
  
  int resultI;

  memcpy(payload_string, payload, length);
  payload_string[length] = '\0';
 
  resultI = atoi(payload_string);

  var = resultI;
    
  
  resultS = "";
  
  for (int i=0;i<length;i++) {
    resultS= resultS + (char)payload[i];
  }
   /*if(resultS=="Foco:1"||resultS=="Foco:0"){
    if(resultS[6]=='1'){
      var=1;
    }else{
      var=0;
    }
   }*/
  Serial.println(resultS);
  Serial.println("-----------------------");

}

void loop() {
   if(!client.connected()) {
    reconnect();
  }
  client.loop();
  if(resultS!="")
    Serial.println(resultS);

   Serial.println(var);
  if(var == 1)
  {
  digitalWrite(2,LOW);
  }
  else if (var == 0)
  {
  digitalWrite(2,HIGH);
  }
  int sensor = analogRead(Photoresistor);
  char datos[40];
  sprintf(datos, "Valor fotoresistencia: %d ", sensor);
  client.publish("esp8266/photo2",datos);
  
  delay(2000);
}
