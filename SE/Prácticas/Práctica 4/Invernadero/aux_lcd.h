//PANTALLA
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_ADDR 0x3C // OLED display address, may vary depending on the module

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_ADDR);

void initPantallaLCD(){
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.display();
  delay(2000);
  display.clearDisplay();
}

//Imprimir Text en pantalla
void PrintText(int X, int Y,String Texto)
{
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(X,Y);
  display.println(Texto);
}

void imprimirEnPantalla(float luz , float temperatura, float humedad){
  display.clearDisplay();
  PrintText(0,0,"TEMPERATURA =  " + String(int(temperatura)) + " C");
  PrintText(0,12,"HUMEDAD =  "+String(int(humedad))+ " %");
  PrintText(0,24,"LUZ =  "+String(luz));

  display.display();
}
