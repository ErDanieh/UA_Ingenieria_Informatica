#include <PubSubClient.h>
WiFiClient wifiClient;
PubSubClient client(wifiClient);//mqtt


const char* mqttServer = "industrial.api.ubidots.com";
const int mqttPort = 1883;

const char* ubidots_token = "BBFF-QOlG4i8VsjPcsJQDGhkBk6jIoi8SKt";
const char* ubidots_username = "grupo_se";
const char* ubidots_password = "@grupose123";

void callback(char* topic, byte* payload, unsigned int length){
  Serial.print("Ha llegado mensaje en el topic[");
  Serial.print(topic);
  Serial.print("]. Mensaje: ");
  for(int i=0; i<length; i++){ Serial.print((char)payload[i]);}
  Serial.println(" ");
}

void suscribeMQTT(char* topic){
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  
  while (!client.connected()) {
    Serial.println("Connecting to MQTT topic...");
    if (client.connect("ESP32", ubidots_token, ubidots_password)) {
      Serial.print("Connected to MQTT topic: ");  
      Serial.println(topic);     	  
      client.subscribe(topic);
    } else {
      Serial.print("Failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void publishMQTT(char* topic, float msg){
  char msgStr[8];
  sprintf(msgStr, "%f", msg);

  if (client.publish(topic, msgStr)) {
     Serial.println((std::string(msgStr) + " publicado correctamente.").c_str()) ;
  }else{
    Serial.println("ERROR: Al publicar");
  }
}

//Envia un único mensaje con varias variables
void sendDataToUbidots(float luz, float temperatura, float humedad){
  char str_luz[10];
  char str_temperatura[10];
  char str_humedad[10];

  char topic[150];
  char payload[300];

  //Para enviar múltiples variables a la vez
  dtostrf(luz, 4, 2, str_luz);
  dtostrf(temperatura, 4, 2, str_temperatura);
  dtostrf(humedad, 4, 2, str_humedad);
  
  sprintf(topic, "%s%s", "/v1.6/devices/", "invernadero");
  sprintf(payload, "%s", ""); // Cleans the payload

  sprintf(payload, "{\"%s\": %s,", "luminico", str_luz); // Adds the variable label
  sprintf(payload, "%s\"%s\": %s,", payload, "temperatura", str_temperatura); // Adds the variable label
  sprintf(payload, "%s\"%s\": %s}", payload, "humedad", str_humedad);

  client.publish(topic, payload);
}

void sendSueloDataToUbidots(float suelo1, float suelo2, float suelo3,float suelo4){
  char str_suelo1[10];
  char str_suelo2[10];
  char str_suelo3[10];
  char str_suelo4[10];

  char topic[150];
  char payload[300];

  //Para enviar múltiples variables a la vez
  dtostrf(suelo1, 4, 2, str_suelo1);
  dtostrf(suelo2, 4, 2, str_suelo2);
  dtostrf(suelo3, 4, 2, str_suelo3);
  dtostrf(suelo4, 4, 2, str_suelo4);
  
  sprintf(topic, "%s%s", "/v1.6/devices/", "invernadero");
  sprintf(payload, "%s", ""); // Cleans the payload

  sprintf(payload, "{\"%s\": %s,", "humedadsuelo", str_suelo1); // Adds the variable label
  sprintf(payload, "%s\"%s\": %s,", payload, "humedadsuelo_2", str_suelo2); // Adds the variable label
  sprintf(payload, "%s\"%s\": %s,", payload, "humedadsuelo_3", str_suelo3);
  sprintf(payload, "%s\"%s\": %s}", payload, "humedadsuelo_4", str_suelo4);

  //Serial.println(payload);
  client.publish(topic, payload);
}

void conectarTopicos(){
  //SENSORES
  suscribeMQTT((char *)"/v1.6/devices/invernadero/luminico/lv");
  suscribeMQTT((char *)"/v1.6/devices/invernadero/humedad/lv");
  suscribeMQTT((char *)"/v1.6/devices/invernadero/temperatura/lv");

  //SUELO
  suscribeMQTT((char *)"/v1.6/devices/invernadero/humedadsuelo/lv");
  suscribeMQTT((char *)"/v1.6/devices/invernadero/humedadsuelo_2/lv");
  suscribeMQTT((char *)"/v1.6/devices/invernadero/humedadsuelo_3/lv");
  suscribeMQTT((char *)"/v1.6/devices/invernadero/humedadsuelo_4/lv");
}
