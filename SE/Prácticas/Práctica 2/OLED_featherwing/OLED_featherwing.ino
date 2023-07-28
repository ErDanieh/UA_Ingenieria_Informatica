#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_ADDR   0x3C // I2C address of OLED display
#define OLED_SDA    A0   // SDA pin for OLED display
#define OLED_SCL    A1   // SCL pin for OLED display

Adafruit_SSD1306 display(OLED_ADDR);

void setup() {
  Serial.begin(9600);

  // Initialize OLED display
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);

  // Print "Hola" on OLED display
  display.setCursor(0, 0);
  display.print("Hola caracolaaaaa");
  display.display();
}

void loop() {
  // Nothing to do here
}
