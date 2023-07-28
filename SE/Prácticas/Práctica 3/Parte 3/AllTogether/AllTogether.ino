#include <Wire.h>
#include "MAX30105.h"
#include <WiFiNINA.h>
#include <ArduinoHttpClient.h>
#include <PubSubClient.h>
#include "heartRate.h"
#include <Adafruit_SSD1306.h>
#include <string>
#include <ArduinoBLE.h>

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

BLEService bleService("19b10010-e8f2-537e-4f6c-d104768a1214"); // UUID for the BLE service
BLEIntCharacteristic intCharacteristic("2A37", BLERead | BLENotify);

void activarBluetooth();
void oledERRORDEDO();
void Blink(int ms);
void BlinkHIGH(int ms);
void BlinkLOW(int ms);

void setup() {
  delay(3000);
  Serial.begin(9600);
  Serial.println("Programa iniciado.");

  conectarWifi();
  subMQTT((char*)"/v1.6/devices/mqtt/pulsaciones/lv");

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.print("SSD1306 allocation failed");
    for (;;)
      ; // Don't proceed, loop forever
  }

  display.display(); // Required by Adafruit Copywrite
  delay(2000);       // Pause for 2 seconds
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
  printText(1, 4, 3, "Inicializando.....");
  display.display();
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  delay(3000);
  digitalWrite(led, LOW);
  delay(500);

  activarBluetooth();
}

void loop() {

  BLEDevice central = BLE.central();


  oledERRORDEDO();
  long irValue = particleSensor.getIR();

  while (beatsPerMinute < 20 || beatsPerMinute > 220) {
    irValue = particleSensor.getIR();

    if (checkForBeat(irValue) == true) {
      long delta = millis() - lastBeat;
      lastBeat = millis();

      beatsPerMinute = 60 / (delta / 1000.0);

      if (beatsPerMinute < 255 && beatsPerMinute > 20) {
        rates[rateSpot++] = (byte)beatsPerMinute;
        rateSpot %= RATE_SIZE;

        beatAvg = 0;
        for (byte x = 0; x < RATE_SIZE; x++) {
          beatAvg += rates[x];
        }
        beatAvg /= RATE_SIZE;
      }
    }

    if (irValue < 50000) {
      linea1 = "ERROR DEDO";
      linea2 = "";
    } else {
      linea1 = "BPM=" + String(int(beatsPerMinute));
      linea2 = "Avg=" + String(beatAvg);
    }

    display.clearDisplay();
    printText(1, 4, 3, linea1);
    printText(1, 4, 18, linea2);
    display.display();

    intCharacteristic.writeValue(beatsPerMinute);
    Serial.println("Enviado valor del sensor al dispositivo conectado mediante BLE!");

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

    // Send data to Ubidots
    String payload = "{\"pulsaciones\":" + String(beatsPerMinute) + "}";
    client.publish("/v1.6/devices/mqtt", payload.c_str());
  }

}

void conectarWifi() {
  int status = WL_IDLE_STATUS;
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, password);
    delay(10000);
  }
  Serial.println("Connected to wifi");
}

void subMQTT(char *topic) {
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP32Client", ubidotsToken, ubidotsPassword)) {
      Serial.println("Connected to MQTT");
    } else {
      Serial.print("Failed with state ");
      Serial.println(client.state());
      delay(2000);
    }
  }
  client.subscribe(topic);
}

void callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void activarBluetooth() {
  if (!BLE.begin()) {
    Serial.println("Failed to initialize BLE!");
    while (1)
      ;
  }
  BLE.setLocalName("DanielAsensiArduino");
  BLE.setAdvertisedService(bleService);
  bleService.addCharacteristic(intCharacteristic);
  BLE.addService(bleService);
  intCharacteristic.writeValue(beatsPerMinute);
  BLE.advertise();
  Serial.println("Bluetooth activado!");
}

void printText(int Size, int X, int Y, String Texto) {
  display.setTextSize(Size);
  display.setTextColor(WHITE);
  display.setCursor(X, Y);
  display.println(Texto);
}

void oledERRORDEDO() {
  display.clearDisplay();
  printText(1, 4, 3, "ERROR DEDO");
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
