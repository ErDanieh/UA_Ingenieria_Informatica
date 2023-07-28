#include <SPI.h>
#include <WiFiNINA.h>
#include <PubSubClient.h>

// Reemplaza estos valores con tus propias credenciales de red WiFi y Ubidots
const char* ssid = "DIGIFIBRA-DDBB";
const char* password = "DKKQJ8QEF7";
const char* ubidotsToken = "BBFF-L5Ortesi8rSvkYiuLzBivbhi6nZQdC";

const char* mqttServer = "industrial.api.ubidots.com";
const int mqttPort = 1883;
const char* mqttTopic = "/v1.6/devices/arduino-33-iot/pulsaciones";

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void setup() {
  Serial.begin(9600);

  // Conexión a la red WiFi
  Serial.print("Conectando a la red WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado!");

  // Configurar cliente MQTT
  mqttClient.setServer(mqttServer, mqttPort);
  mqttClient.setCallback(mqttCallback);

  // Conectar al servidor MQTT
  conectarMQTT();
}

void loop() {
  // Mantener la conexión MQTT
  if (!mqttClient.connected()) {
    conectarMQTT();
  }

  // Procesar mensajes entrantes
  mqttClient.loop();
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensaje MQTT recibido: ");
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println(message);
}

void conectarMQTT() {
  Serial.print("Conectando al servidor MQTT...");
  while (!mqttClient.connected()) {
    if (mqttClient.connect("arduinoClient", ubidotsToken, "")) {
      Serial.println("Conectado!");
      mqttClient.subscribe(mqttTopic);
    } else {
      Serial.print("Error en la conexión (");
      Serial.print(mqttClient.state());
      Serial.println("). Reintentando en 5 segundos...");
      delay(5000);
    }
  }
}
