#include <Wire.h>
#include "MAX30105.h"
#include <WiFiNINA.h>
#include "heartRate.h"
#include <Adafruit_SSD1306.h>
#include <string>
#include <ArduinoBLE.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET -1

void Blink(int);

MAX30105 particleSensor;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const byte RATE_SIZE = 4; // Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; // Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; // Time at which the last beat occurred

float beatsPerMinute = 0;
int beatAvg;

// Pantalla
int TextSize = 1; // tamaño del texto a imprimir
bool TextInverted = false; // false=Texto normal, true=Texto invertido
String Texto; // Texto a imprimir
int TextX; // Ubicacion en X del texto
int TextY; // Ubicacion en Y del texto
bool ClearScreen = false; // Limpiar pantalla
String Linea1;
String Linea2;

int led = 13;

BLEService bleService("19b10010-e8f2-537e-4f6c-d104768a1214"); // UUID for the BLE service
BLEIntCharacteristic intCharacteristic("2A37", BLERead | BLENotify);
// Custom characteristic UUID

void activarBluetooth();

void setup() {
  delay(3000);
  Serial.begin(9600);
  Serial.println("Programa iniciado.");

  activarBluetooth();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.print("SSD1306 allocation failed");
    for (;;); // Don’t proceed, loop forever
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

  Serial.println("Esperando conexión bluetooth...");
}

bool shown = false;

void loop() {
  BLEDevice central = BLE.central();
  if (central) {
    if (!shown) {
      Serial.print("Connected to central: ");
      Serial.println(central.address());
      digitalWrite(LED_BUILTIN, HIGH);
      shown = true;
    }

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
        for (byte x = 0; x < RATE_SIZE; x++) {
          beatAvg += rates[x];
        }
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
      if (int(beatsPerMinute) >= 70 && int(beatsPerMinute) < 110) {
        // Blink CADA SEGUNDO EN 5 SEGUNDOS
        Blink(1000); // 2s
        Blink(1000); // 2s
        BlinkHIGH(1000); // 1s
        digitalWrite(led, LOW);
      } else {
        if (int(beatsPerMinute) > 110) {
          // Blink CADA MEDIO SEGUNDO EN 5 SEGUNDOS
          Blink(500); // 1s
          Blink(500); // 1s
          Blink(500); // 1s
          Blink(500); // 1s
          Blink(500); // 1s
        }
      }
    }

    // Envío de datos por Bluetooth
    intCharacteristic.writeValue(beatsPerMinute);
    Serial.println("Enviado valor del sensor al dispositivo conectado mediante BLE!");

    beatsPerMinute = 0;
  }
}

// FUNCIONES //////////////////////////
void activarBluetooth() {
  if (!BLE.begin()) {
    Serial.println("Failed to initialize BLE!");
    while (1);
  }

  // Set the local name and advertised service UUID:
  BLE.setLocalName("DanielAsensiArduino");
  BLE.setAdvertisedService(bleService);

  // Add the characteristic to the service:
  bleService.addCharacteristic(intCharacteristic);

  // Advertise the service:
  BLE.addService(bleService);

  intCharacteristic.writeValue(beatsPerMinute);

  // Start advertising:
  BLE.advertise();

  Serial.println("Bluetooth activado!");
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
