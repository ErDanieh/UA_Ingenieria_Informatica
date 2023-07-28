#include <Wire.h>
#include <SPI.h>
#include "MAX30105.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_ADDR   0x3C // I2C address of OLED display
#define OLED_SDA    A4   // SDA pin for OLED display
#define OLED_SCL    A5   // SCL pin for OLED display
Adafruit_SSD1306 display(OLED_ADDR);


#include "heartRate.h"

MAX30105 particleSensor;

const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred

float beatsPerMinute;
int beatAvg;

void setup()
{
  Serial.begin(115200);
  Serial.println("Initializing...");
  
  pinMode(5, OUTPUT); // Red LED
  pinMode(6, OUTPUT); // Blue LED
  pinMode(7, OUTPUT); // Green LED

  // Initialize sensor
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }
  Serial.println("Place your index finger on the sensor with steady pressure.");

  particleSensor.setup(); //Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
  particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED
  //Serial.begin(9600);

  // Initialize OLED display
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);

  // Print "Hola" on OLED display
  display.setCursor(0, 0);
  display.print("Inicializando");
  display.display();
}

void loop()
{
  display.clearDisplay();
  static unsigned long lastColorChangeTime = 0; // Time of last color change
  long irValue = particleSensor.getIR();

  if (checkForBeat(irValue) == true)
  {
    //We sensed a beat!
    long delta = millis() - lastBeat;
    lastBeat = millis();

    beatsPerMinute = 60 / (delta / 1000.0);

    if (beatsPerMinute < 255 && beatsPerMinute > 0)
    {
      rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
      rateSpot %= RATE_SIZE; //Wrap variable

      //Take average of readings
      beatAvg = 0;
      for (byte x = 0 ; x < RATE_SIZE ; x++)
        beatAvg += rates[x];
      beatAvg /= RATE_SIZE;

      // Change LED color depending on beatAvg
      if (beatAvg > 0) {
        if (beatAvg < 60) {
          digitalWrite(5, HIGH); // Red
          digitalWrite(6, LOW); // Blue
          digitalWrite(7, LOW); // Green
          display.setCursor(0, 0);
          display.print("BPM: ");
          display.print(beatAvg);
          display.display();
        } else if (beatAvg < 120) {
          digitalWrite(5, LOW); // Red
          digitalWrite(6, HIGH); // Blue
          digitalWrite(7, LOW); // Green
          display.setCursor(0, 0);
          display.print("BPM: ");
          display.print(beatAvg);
          display.display();
        } else {
          digitalWrite(5, LOW); // Red
          digitalWrite(6, LOW); // Blue
          digitalWrite(7, HIGH); // Green
          display.setCursor(0, 0);
          display.print("BPM: ");
          display.print(beatAvg);
          display.display();
        }
    }
    else{

          digitalWrite(5, LOW); // Red
          digitalWrite(6, LOW); // Blue
          digitalWrite(7, LOW); // Green
          display.setCursor(0, 0);
          display.print("ERROR DEDO");
          display.display();
      
    }
    Serial.print(beatAvg);
    }
  }
  
 }
