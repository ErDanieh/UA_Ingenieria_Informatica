#include <SPI.h>
#include <WiFiNINA.h>
#include <ArduinoHttpClient.h>

// Reemplaza estos valores con tus propias credenciales de red WiFi y Ubidots
const char* ssid = "DIGIFIBRA-DDBB";
const char* password = "DKKQJ8QEF7";
const char* ubidotsToken = "BBFF-L5Ortesi8rSvkYiuLzBivbhi6nZQdC";
const char* variableId = "640ede7a2fca68000c6f6a31";

int status = WL_IDLE_STATUS;

const char* server = "industrial.api.ubidots.com";
int port = 80;

WiFiClient wifiClient;
HttpClient httpClient = HttpClient(wifiClient, server, port);

void setup() {
  Serial.begin(9600);

  // Conexión a la red WiFi
  Serial.print("Conectando a la red WiFi...");
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, password);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println("Connected to WiFi");

}

void loop() {
  // Genera un entero aleatorio entre 60 y 120
  int pulso = random(60, 121);

  // Enviar la media de las pulsaciones a Ubidots
  enviarPulsaciones(pulso);

  // Espera 5 segundos antes de enviar el siguiente valor
  delay(5000);
}

void enviarPulsaciones(int pulso) {
  Serial.print("Enviando pulsaciones: ");
  Serial.println(pulso);

  // Crear la ruta y el cuerpo del mensaje
  String ruta = "/api/v1.6/variables/" + String(variableId) + "/values";
  String contenido = "{\"value\":" + String(pulso) + "}";

  // Conectar y enviar el mensaje a Ubidots
  httpClient.beginRequest();
  httpClient.post(ruta);
  httpClient.sendHeader("X-Auth-Token", ubidotsToken);
  httpClient.sendHeader("Content-Type", "application/json");
  httpClient.sendHeader("Content-Length", contenido.length());
  httpClient.beginBody();
  httpClient.print(contenido);
  httpClient.endRequest();

  // Leer y mostrar la respuesta del servidor
  int statusCode = httpClient.responseStatusCode();
  String response = httpClient.responseBody();
  Serial.print("Código de estado: ");
  Serial.println(statusCode);
  Serial.print("Respuesta: ");
  Serial.println(response);
}
