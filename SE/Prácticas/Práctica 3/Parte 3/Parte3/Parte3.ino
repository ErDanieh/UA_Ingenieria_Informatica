#include <Wire.h>
#include "MAX30105.h"
#include <WiFiNINA.h>
#include <ArduinoHttpClient.h>
#include <PubSubClient.h>
#include "heartRate.h"
#include <Adafruit_SSD1306.h>
#include <string>
#include <ArduinoBLE.h>
#include <sstream>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET -1

MAX30105 particleSensor;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const byte RATE_SIZE = 4; // Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; // Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; // Time at which the last beat occurred

float beatsPerMinute;
int beatAvg;

// Pantalla
int TextSize = 1; // tamaño del texto a imprimir
bool TextInverted = false; // false = Texto normal, true = Texto invertido
String Texto; // Texto a imprimir
int TextX; // Ubicacion en X del texto
int TextY; // Ubicacion en Y del texto
bool ClearScreen = false; // Limpiar pantalla
String Linea1;
String Linea2;

int led = 13;

// AMPLIACIÓN PRÁCTICA 3
// mqtt
void subMQTT(char*);
void callback(char*, byte*, unsigned int);
// Credenciales de WiFi
void conectarWifi();
const char* ssid = "DIGIFIBRA-DDBB";
const char* password = "DKKQJ8QEF7";
// Credenciales de cuenta ubidots
const char* ubidots_token = "BBFF-L5Ortesi8rSvkYiuLzBivbhi6nZQdC";
const char* ubidots_password = "@midad2133";
WiFiClient wifiClient;
PubSubClient client(wifiClient); // mqtt
const char* mqttServer = "industrial.api.ubidots.com";
const int mqttPort = 1883;

BLEService bleService("19b10010-e8f2-537e-4f6c-d104768a1214"); // UUID for the BLE service
BLECharacteristic randomChar("19b10011-e8f2-537e-4f6c-d104768a1214", BLERead | BLENotify, 2); // UUID for the BLE characteristic, 2 bytes

bool puedeContinuar = false;

void setup() {
  delay(3000);
  Serial.begin(9600);
  Serial.println("Programa iniciado.");

  conectarWifi();
  subMQTT((char*)"/v1.6/devices/mqtt/received-text/lv");

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.print("SSD1306 allocation failed");
    for (;;); // Don't proceed, loop forever
  }

  display.display(); // Requerido por Adafruit Copywrite
  delay(2000); // Pause for 2 seconds
  display.clearDisplay();

  // Initialize sensor
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) { // Use default I2C port, 400kHz speed
    Serial.println("MAX30105 was not found. Please check wiring/power.");
    while (1);
  }
  particleSensor.setup(); // Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A); // Turn Red LED to low to indicate sensor is running
  particleSensor.setPulseAmplitudeGreen(0); // Turn off Green LED

  display.clearDisplay();
  imprimirOLED(1, 4, 3, "Inicializando...");
  display.display();
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  delay(3000);
  digitalWrite(led, LOW);
  delay(500);
}

void loop() {
  client.loop();

  if (puedeContinuar) {
    oledERRORDEDO();
    long irValue = particleSensor.getIR();

    if (checkForBeat(irValue) == true) {
      // We sensed a beat!
      long delta = millis() - lastBeat;
      lastBeat = millis();

      beatsPerMinute = 60 / (delta / 1000.0);

      if (beatsPerMinute < 255 && beatsPerMinute > 20) {
        rates[rateSpot++] = (byte)beatsPerMinute; // Store this reading in the array
        rateSpot %= RATE_SIZE; // Wrap variable

        // Take average of readings
        beatAvg = 0;
        for (byte x = 0; x < RATE_SIZE; x++)
          beatAvg += rates[x];
        beatAvg /= RATE_SIZE;
      }
    }

    if (irValue < 50000) {
      Linea1 = "ERROR DEDO";
      Linea2 = "";
    } else {
      Linea1 = "BPM=" + String(int(beatsPerMinute));
      Linea2 = "Avg=" + String(beatAvg);
    }

    display.clearDisplay();
    imprimirOLED(1, 4, 3, Linea1);
    imprimirOLED(1, 4, 18, Linea2);
    display.display();

    // LED
    if (int(beatsPerMinute) < 70) { // FIJO
      digitalWrite(led, HIGH);
      delay(5000); // delay 5 segundos
      digitalWrite(led, LOW);
    } else {
      if (int(beatsPerMinute) >= 70 && int(beatsPerMinute) < 110) { // Blinck CADA SEGUNDO EN 5 SEGUNDOS
        Blinck(1000); // 2s
        Blinck(1000); // 2s
        BlinckHIGH(1000); // 1s
        digitalWrite(led, LOW);
      } else {
        if (int(beatsPerMinute) > 110) { // Blinck CADA MEDIO SEGUNDO EN 5 SEGUNDOS
          Blinck(500); // 1s
          Blinck(500); // 1s
          Blinck(500); // 1s
          Blinck(500); // 1s
          Blinck(500); // 1s
        }
      }
    }

    beatsPerMinute = 0;
  }
}

//// FUNCIONES //////////////////////////
void subMQTT(char* topic) {
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP32", ubidots_token, ubidots_password)) {
      Serial.println("Connected to MQTT");
      client.subscribe(topic);
    } else {
      Serial.print("Failed with state");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void conectarWifi() {
  while (WiFi.begin(ssid, password) != WL_CONNECTED) {
    Serial.print("Conectando a");
    Serial.print(ssid);
    Serial.println("...");
    delay(5000);
  }
  Serial.println("Conectado a la red wifi correctamente!");
}

// MQTT
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Ha llegado mensaje en el topic[");
  Serial.print(topic);
  Serial.print("]. Mensaje:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    if ((char)payload[i] == '1') {
      Serial.println("");
      puedeContinuar = true;
      oledERRORDEDO();
      Serial.println("Programa activado.");
      break;
    }
    if ((char)payload[i] == '0') {
      Serial.println("");
      puedeContinuar = false;
      oledDESACTIVADO();
      Serial.println("Programa desactivado.");
      break;
    }
  }
  Serial.println("");
}

// Imprimir Text en pantalla
void imprimirOLED(int Size, int X, int Y, String Texto) {
  display.setTextSize(Size);
  display.setTextColor(WHITE);
  display.setCursor(X, Y);
  display.println(Texto);
}

void oledERRORDEDO() {
  display.clearDisplay();
  imprimirOLED(1, 4, 3, "ERROR DEDO");
  digitalWrite(led, HIGH);
  display.display();
}
void oledDESACTIVADO() {
  Linea1 = String("SUSPENDIDO");
  Linea2 = "";
  display.clearDisplay();
  imprimirOLED(1, 4, 3, Linea1);
  imprimirOLED(1, 4, 18, Linea2);
  display.display();
}

void Blinck(int ms) {
  BlinckHIGH(ms);
  BlinckLOW(ms);
}

void BlinckHIGH(int ms) {
  digitalWrite(led, HIGH);
  delay(ms);
}

void BlinckLOW(int ms) {
  digitalWrite(led, LOW);
  delay(ms);
}
