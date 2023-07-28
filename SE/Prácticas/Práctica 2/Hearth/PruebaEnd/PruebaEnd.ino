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

const byte RATE_SIZE = 4; // Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; // Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; // Time at which the last beat occurred
float beatsPerMinute;
int beatAvg;

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing...");
  
  pinMode(5, OUTPUT); // Red LED
  pinMode(6, OUTPUT); // Blue LED
  pinMode(7, OUTPUT); // Green LED

  // Initialize sensor
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) // Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }

  particleSensor.setup(); // Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A); // Turn Red LED to low to indicate sensor is running
  particleSensor.setPulseAmplitudeGreen(0); // Turn off Green LED

  // Initialize OLED display
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);

  // Display "Inicializando..." on OLED display
  display.setCursor(0, 0);
  display.print("Inicializando...");
  display.display();

  // Wait for 3 seconds while the LED is on and the message is displayed on the OLED screen
  digitalWrite(5, HIGH); // Turn on LED
  delay(3000);
  digitalWrite(5, LOW); // Turn off LED
}

void loop() {
  static unsigned long lastReadingTime = 0; // Time of last sensor reading
  long irValue = particleSensor.getIR();
  
  if (irValue == 0) {
    // No finger detected on sensor
    digitalWrite(5, LOW); // Red
    digitalWrite(6, LOW); // Blue
    digitalWrite(7, LOW); // Green
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("ERROR DEDO");
    display.display();
    return; // Exit loop
  }

  // Check for a heart beat
  if (checkForBeat(irValue) == true) {
    long delta = millis() - lastBeat;
    lastBeat = millis();
    beatsPerMinute = 60 / (delta / 1000.0);
    
    // Store the heart rate reading in the array
    if (beatsPerMinute < 255 && beatsPerMinute > 0) {
      rates[rateSpot++] = (byte)beatsPerMinute;
      rateSpot %= RATE_SIZE;

      // Take average of readings
      beatAvg = 0;
      for (byte x = 0 ; x < RATE_SIZE ; x++)
        beatAvg += rates[x];
      
      beatAvg /= RATE_SIZE;
        // Change LED color and display heart rate on OLED screen
  if (beatAvg < 70) {
    digitalWrite(6, LOW); // Blue
    digitalWrite(7, LOW); // Green
    digitalWrite(5, HIGH); // Red
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("BPM: ");
    display.print(beatAvg);
    display.display();
  } else if (beatAvg < 110) {
    digitalWrite(6, HIGH); // Blue
    digitalWrite(7, LOW); // Green
    digitalWrite(5, digitalRead(5) ^ 1); // Toggle Red LED
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("BPM: ");
    display.print(beatAvg);
    display.display();
  } else {
    digitalWrite(6, LOW); // Blue
    digitalWrite(7, HIGH); // Green
    digitalWrite(5, digitalRead(5) ^ 1); // Toggle Red LED
    delay(500);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("BPM: ");
    display.print(beatAvg);
    display.display();
  }
} else {
  // Display "ERROR DEDO" on OLED screen when no finger is detected on the sensor
  digitalWrite(5, LOW); // Red
  digitalWrite(6, LOW); // Blue
  digitalWrite(7, LOW); // Green
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("ERROR DEDO");
  display.display();
}

// Check if it's time to take another sensor reading
if (millis() - lastReadingTime > 5000) {
lastReadingTime = millis();
particleSensor.check(); // Check the sensor for new data
}
}
}
