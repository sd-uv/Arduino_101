//******************************************************************************
// Elementos de biblioteca que son necesarios para emplear el sensor.
#include <Wire.h>
#include <Adafruit_BMP085.h>

/*******************************************************************************
  This is an example for the BMP085 Barometric Pressure & Temp Sensor

  Designed specifically to work with the Adafruit BMP085 Breakout 
  ----> https://www.adafruit.com/products/391

  These displays use I2C to communicate, 2 pins are required to interface.
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution

// Connect VCC of the BMP085 sensor to 3.3V (NOT 5.0V!)
// Connect GND to Ground
// Connect SCL to i2c clock - on '168/'328 Arduino Uno/Duemilanove/etc 
//                            Thats Analog 5 (A5)
// Connect SDA to i2c data - on '168/'328 Arduino Uno/Duemilanove/etc 
//                            Thats Analog 4 (A4)
// EOC is not used, it signifies an end of conversion
// XCLR is a reset pin, also not used here

*******************************************************************************/
// Creación de una variable (bmp) del tipo:
//  "Sensor de Presión Barométrica / Temperatura"
// A esta acción se le llama "instanciación" o creación de una "instancia"
Adafruit_BMP085 bmp;

// Ajustes
void setup() {
  Serial.begin(9600);
  // Verifica si está disponible el módulo de Presión / Temperatura
  if (!bmp.begin()) {
	  //Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    Serial.println("No se puede encontrar un sensor BMP085");
    Serial.println(" - REVISE la CIRCUITERIA - ");
    // Nos quedaremos "atascados" en la siguiente instrucción.
	  while (1) {
    }
  }
}

//******************************************************************************
// Ejecución del lazo que conforma el programa principal:
void loop() {
  Serial.print("Temperatura = ");
  Serial.print(bmp.readTemperature());
  Serial.println(" *C");
    
  Serial.print("Presion = ");
  Serial.print(bmp.readPressure());
  Serial.println(" Pa");
    
  // Cálculo de la altitud asumiendo barómetros 'estándard'
  // La presión de 1013.25 millibares = 101325 Pascal
  Serial.print("Altitud = ");
  Serial.print(bmp.readAltitude());
  Serial.println(" metros");

  // Se puede obtener una medición más precisa de la altitud si se conoce la actual
  // presión al nivel del mar, la cual varía con las condiciones atmosféricas.
  // Si la condición actual de la presión barométrica al nivel del mar
  // fuera de 1015 milibares, la presión barométrica sería de 10150 Pascales.
  Serial.print("Altitud Real = ");
  Serial.print(bmp.readAltitude(101500));
  Serial.println(" metros");
    
  Serial.println();
  delay(500);
}
