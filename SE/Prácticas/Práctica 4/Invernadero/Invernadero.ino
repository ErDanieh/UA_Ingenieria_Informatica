#include <Wire.h>
#include <WiFiNINA_Generic.h>
#include "MAX30105.h"
#include <ArduinoHttpClient.h>
#include "heartRate.h"
#include <string> 
#include <ArduinoBLE.h>
#include <sstream>
#include <stdlib.h>
#include <avr/dtostrf.h>

//AUXILIARES
#include "aux_wifi.h"
#include "aux_mqtt.h"
#include "aux_telegram.h"
#include "aux_sensores.h"
#include "aux_lcd.h"

//LED 
#define BLUE_PIN 2
#define GREEN_PIN 3
#define RED_PIN 4

// Variables to store the color values
int redValue = 0;
int greenValue = 0;
int blueValue = 0;

void setup() { 
  
  delay(3000); //delay para que inicio el draw
  Serial.begin(9600);
  Serial.println("Programa iniciado.");

  dht.begin(); //para que funcione el sensor de temp. y humedad.

  //LED
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  //PANTALLA
  initPantallaLCD(); 
  colorled(1); //ROJO

  //WIFI
  conectarWifi(); 
  colorled(2); //VERDE

  //MQTT
  conectarTopicos();
}

void loop() {
  client.loop(); //para que recibamos del productor de mqtt

  //DATOS SENSORES
  float luz = getLuz(); if(isnan(luz)){luz=-1;}
  float temperatura = getTemperatura(); if(isnan(temperatura)){temperatura=-1;}
  float humedad = getHumedad(); if(isnan(humedad)){humedad=-1;}
  sendDataToUbidots(luz,temperatura,humedad);
  Serial.print("Luz: ");  Serial.print(luz); Serial.print(" , Temperatura: ");Serial.print(temperatura);Serial.print( " , Humedad: ");Serial.println(humedad);
 
  float humedadSuelo1 = getHumedadSuelo(1);
  float humedadSuelo2 = getHumedadSuelo(2);
  float humedadSuelo3 = getHumedadSuelo(3);
  float humedadSuelo4 = getHumedadSuelo(4);
  sendSueloDataToUbidots(humedadSuelo1,humedadSuelo2, humedadSuelo3,humedadSuelo4);
  Serial.print("Suelo1: ");  Serial.println(humedadSuelo1); // Serial.print(" , Suelo2: ");Serial.print(humedadSuelo2);Serial.print( " , Suelo3: ");Serial.print(humedadSuelo3);Serial.print( " , Suelo4: ");Serial.println(humedadSuelo4);
  
  //LED
  analogWrite(RED_PIN, 255); 
  analogWrite(GREEN_PIN, 120); 
  analogWrite(BLUE_PIN, 0);

  //PANTALLA
  imprimirEnPantalla(luz,temperatura,humedad);
 
  delay(2000);

}

void colorled(int color){
  // Process the user input and change the LED color accordingly
  switch (color) {
    case 1:  // Red
      redValue = 255;
      greenValue = 0;
      blueValue = 0;
      break;
    case 2:  // Green
      redValue = 0;
      greenValue = 255;
      blueValue = 0;
      break;
    case 3:  // Blue
      redValue = 0;
      greenValue = 0;
      blueValue = 255;
      break;
    default: // Invalid input
      Serial.println("Invalid color input!");
      return;
  }

  // Update the LED color
  analogWrite(RED_PIN, redValue);
  analogWrite(GREEN_PIN, greenValue);
  analogWrite(BLUE_PIN, blueValue);
}
