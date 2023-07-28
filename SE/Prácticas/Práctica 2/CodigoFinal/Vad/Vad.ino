#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"
#include <Adafruit_SSD1306.h>

// Constantes
const byte RATE_SIZE = 4; // Aumenta para una media móvil mayor
const int LED_PIN = 7;
const int LED_PIN_VERDE = 6;
const int SCREEN_WIDTH = 128;
const int SCREEN_HEIGHT = 32;
const int OLED_RESET = -1;
const int TEXT_SIZE = 1;
const int TEXT_X = 1;
const int TEXT_Y = 4;
const int DELAY_BEFORE_START = 2000;
const int DELAY_BETWEEN_PULSES = 5000;
const int BEATS_PER_MINUTE_NORMAL = 70;
const int BEATS_PER_MINUTE_WARNING = 110;
const int BEATS_PER_MINUTE_LIMIT = 255;
const int PULSE_AMPLITUDE_RED = 0x0A;

// Variables globales
MAX30105 particleSensor;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
byte rates[RATE_SIZE]; // Array de latidos por minuto
byte rateSpot = 0;     // Índice actual del array
long lastBeat = 0;     // Tiempo del último latido
float beatsPerMinute;  // Latidos por minuto
int beatAvg;           // Promedio de latidos por minuto
String linea1;         // Primera línea del texto a mostrar
String linea2;         // Segunda línea del texto a mostrar

// Configuración inicial
void setup()
{
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println("SSD1306 allocation failed");
    while (1)
      ;
  }

  Serial.print("HOLA");

  display.display();
  delay(DELAY_BEFORE_START);
  display.clearDisplay();

  if (!particleSensor.begin(Wire, I2C_SPEED_FAST))
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1)
      ;
  }

  particleSensor.setup();
  particleSensor.setPulseAmplitudeRed(PULSE_AMPLITUDE_RED);
  particleSensor.setPulseAmplitudeGreen(0);

  display.clearDisplay();
  printText(TEXT_SIZE, TEXT_X, TEXT_Y, "Inicializando...");
  display.display();

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  delay(3000);
  digitalWrite(LED_PIN, LOW);
  delay(500);
}

// Bucle principal
void loop()
{

  long irValue = particleSensor.getIR();

  while(irValue < 50000){
    irValue = particleSensor.getIR();
    Serial.print(irValue + "\n");
    printPulseErrorIfPresent();    
  }

  digitalWrite(LED_PIN,LOW);  
  
  while (beatsPerMinute < BEATS_PER_MINUTE_NORMAL)
  {
    irValue = particleSensor.getIR();

    if (checkForBeat(irValue) == true)
    {
      long delta = millis() - lastBeat;
      lastBeat = millis();

      beatsPerMinute = 60 / (delta / 1000.0);

      if (beatsPerMinute < BEATS_PER_MINUTE_LIMIT && beatsPerMinute > BEATS_PER_MINUTE_NORMAL)
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

  if (irValue < 50000)
  {
    linea1 = "ERROR DEDO";
    linea2 = "";
  }
  else
  {
    linea1 = "BPM = " + String(int(beatsPerMinute));
    linea2 = "Avg = " + String(beatAvg);
  }

  display.clearDisplay();
  printText(TEXT_SIZE, TEXT_X, TEXT_Y, linea1);
  printText(TEXT_SIZE, TEXT_X, TEXT_Y + 14, linea2);
  display.display();

    if (int(beatsPerMinute) < 70){ //FIJO
      digitalWrite(LED_PIN,HIGH);
      delay(5000); //delay 5 segundos
      digitalWrite(LED_PIN,LOW); 
    }else{
      if(int(beatsPerMinute) >= 70 && int(beatsPerMinute) < 110){ //PARDPADEO CADA SEGUNDO EN 5 SEGUNDOS
          blink(1000); //2s
          blink(1000); //2s
          blinkHIGH(1000); //1s
          digitalWrite(LED_PIN,LOW); 
      }else{
        if(int(beatsPerMinute) > 110){ //PARDPADEO CADA MEDIO SEGUNDO EN 5 SEGUNDOS
          blink(500); //1s
          blink(500); //1s
          blink(500); //1s
          blink(500); //1s
          blink(500); //1s
        }
      }
    }
  beatsPerMinute = 0;
}

// Imprime un error si la intensidad de luz es demasiado baja
void printPulseErrorIfPresent()
{
  display.clearDisplay();
  printText(TEXT_SIZE, TEXT_X, TEXT_Y, "ERROR DEDO");
  digitalWrite(LED_PIN, HIGH);
  display.display();
}

// Imprime texto en la pantalla OLED
void printText(int size, int x, int y, String text)
{
  display.setTextSize(size);
  display.setTextColor(WHITE);
  display.setCursor(x, y);
  display.println(text);
}

// Hace parpadear el LED
void blink(int ms){
  blinkHIGH(ms);
  blinkLOW(ms);
}

void blinkHIGH(int ms){
    digitalWrite(LED_PIN_VERDE,HIGH);
    delay(ms);   
}

void blinkLOW(int ms){
    digitalWrite(LED_PIN_VERDE,LOW);  
    delay(ms);  
}
