#include <Wire.h>
#include "MAX30105.h"
#include <WiFiNINA.h>
#include <ArduinoHttpClient.h>
#include <PubSubClient.h>
#include "heartRate.h"
#include <Adafruit_SSD1306.h>
#include <string>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET -1

MAX30105 particleSensor;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const byte RATE_SIZE = 4;
byte rates[RATE_SIZE];
byte rateSpot = 0;
long lastBeat = 0;

float beatsPerMinute;
int beatAvg;

int textSize = 1;
bool textInverted = false;
String texto;
int textX;
int textY;
bool clearScreen = false;
String linea1;
String linea2;

int led = 13;

void subMQTT(char*);
void callback(char*, byte*, unsigned int);
void conectarWifi();
const char* ssid = "DIGIFIBRA-DDBB";
const char* password = "DKKQJ8QEF7";
const char* ubidotsToken = "BBFF-L5Ortesi8rSvkYiuLzBivbhi6nZQdC";
const char* ubidotsPassword = "@dani2703";
WiFiClient wifiClient;
PubSubClient client(wifiClient);
const char* mqttServer = "industrial.api.ubidots.com";
const int mqttPort = 1883;

void setup() {
  delay(3000);
  Serial.begin(9600);
  Serial.println("Programa iniciado.");

  conectarWifi();
  subMQTT((char*)"/v1.6/devices/mqtt/pulsaciones/lv");

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.print("SSD1306 allocation failed");
    for (;;)
      ; 
  }

  display.display(); 
  delay(2000);     
  display.clearDisplay();

  // Initialize sensor
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {
    Serial.println("MAX30105 was not found. Please check wiring/power.");
    while (1)
      ;
  }
  particleSensor.setup();
  particleSensor.setPulseAmplitudeRed(0x0A);
  particleSensor.setPulseAmplitudeGreen(0);

  display.clearDisplay();
  imprimirOLED(1, 4, 3, "Inicializando.....");
  display.display();
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  delay(3000);
  digitalWrite(led, LOW);
  delay(500);
}

void loop() {
  client.loop();

  oledERRORDEDO();
  long irValue = particleSensor.getIR();

  while (beatsPerMinute < 70) {
    irValue = particleSensor.getIR();

    if (checkForBeat(irValue) == true) {
      long delta = millis() - lastBeat;
      lastBeat = millis();

      beatsPerMinute = 60 / (delta / 1000.0);

      if (beatsPerMinute < 255 && beatsPerMinute > 20)
      {
        rates[rateSpot++] = (byte)beatsPerMinute;
        rateSpot %= RATE_SIZE;
        beatAvg = 0;
        for (byte x = 0; x < RATE_SIZE; x++)
          beatAvg += rates[x];
        beatAvg /= RATE_SIZE;
      }
    }
  }

  if (irValue < 50000) {
    linea1 = "ERROR DEDO";
    linea2 = "";
  } else {
    linea1 = "BPM =" + String(int(beatsPerMinute));
    linea2 = "Avg =" + String(beatAvg);
  }

  display.clearDisplay();
  imprimirOLED(1, 4, 3, linea1);
  imprimirOLED(1, 4, 18, linea2);
  display.display();

  if (int(beatsPerMinute) < 70) {
    digitalWrite(led, HIGH);
    delay(5000);
    digitalWrite(led, LOW);
  } else {
    if (int(beatsPerMinute) >= 70 && int(beatsPerMinute) < 110) {
      Blink(1000);
      Blink(1000);
      BlinkHIGH(1000);
      digitalWrite(led, LOW);
    } else {
      if (int(beatsPerMinute) > 110) {
        Blink(500);
        Blink(500);
        Blink(500);
        Blink(500);
        Blink(500);
      }
    }
  }

  if (client.publish("/v1.6/devices/mqtt/received-text", (std::string("{\"value\":") + std::to_string(beatsPerMinute) + "}").c_str())) {
    Serial.println((std::string("Valor ") + std::to_string(beatsPerMinute) + " publicado correctamente.").c_str());
  }


  beatsPerMinute = 0;
}

void subMQTT(char* topic) {
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP32", ubidotsToken, ubidotsPassword)) {
      Serial.println("Connected to MQTT");
      client.subscribe(topic);
    } else {
      Serial.print("Failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void conectarWifi() {
  while (WiFi.begin(ssid, password) != WL_CONNECTED) {
    Serial.print("Conectando a ");
    Serial.print(ssid);
    Serial.println("...");
    delay(5000);
  }
  Serial.println("Conectado a la red wifi correctamente!");
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Ha llegado mensaje en el topic[");
  Serial.print(topic);
  Serial.print("]. Mensaje:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println("");
}

void imprimirOLED(int size, int x, int y, String texto) {
  display.setTextSize(size);
  display.setTextColor(WHITE);
  display.setCursor(x, y);
  display.println(texto);
}

void oledERRORDEDO() {
  display.clearDisplay();
  imprimirOLED(1, 4, 3, "ERROR DEDO");
  digitalWrite(led, HIGH);
  display.display();
}

void Blink(int ms) {
  BlinkHIGH(ms);
  BlinkLOW(ms);
}

void BlinkHIGH(int ms) {
  digitalWrite(led, HIGH);
  delay(ms);
}

void BlinkLOW(int ms) {
  digitalWrite(led, LOW);
  delay(ms);
}
