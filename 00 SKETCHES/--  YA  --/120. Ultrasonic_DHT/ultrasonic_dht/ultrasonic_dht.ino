//------------------------------------------------------------------------------
// Programa para Ejercitar un Sensor de Distancia Ultrasónico HC-S04
//
// Las conexiones que se emplean normalmente son:
//  Sensor HC-S04 Vcc       -->   Arduino 5V
//  Sensor HC-S04 Gnd       -->   Arduino GND
//  Sensor HC-S04 Echo      -->   Arduino Pin 13
//  Sensor HC-S04 Trigger   -->   Arduino Pin 12
//  Sensor HC-S04 Red POS   -->   Arduino Pin 11
//  Sensor HC-S04 Green POS -->   Arduino Pin 10
//
// Base para este código:
// http://en.wikiversity.org/wiki/User:Dstaub/robotcar
//------------------------------------------------------------------------------
//-----[ BIBLIOTECAS ]-----
#include "DHT.h"
//-----[Constantes y Variables ]-----
#define DHTPIN 2          // Pin empleado para sensor Humedad / Temperatura
#define DHTTYPE DHT22     // Tipo de sensor utilizado (Puede ser DHT11)

#define trigPin 13        // Pines para el sensor ultrasónico
#define echoPin 12        //

DHT dht(DHTPIN, DHTTYPE); // Creación de un objeto para sensado Hum / Tmp
float lasttemp;           // Variable
//------------------------------------------------------------------------------
void setup() {
  Serial.begin (9600);        // Velocidad de la comunicación serial
  pinMode(trigPin, OUTPUT);   // Declaración de pin como salida
  pinMode(echoPin, INPUT);    // Declaración de pin como salida
  dht.begin();                // Puesta a punto del sensor de Hum / Tmp
}
//------------------------------------------------------------------------------
void loop() {
  long duration;              // Variables
  float distance;             //

  digitalWrite(trigPin, LOW);   // Prepara la línea que genera el pulso...
  delayMicroseconds(2);         // ...de disparo ("Trigger")
  digitalWrite(trigPin, HIGH);  // Genera el disparo...
  delayMicroseconds(10);        // ... con al menos este ancho de pulso
  digitalWrite(trigPin, LOW);   // Concluye el disparo
  duration = pulseIn(echoPin, HIGH);  // Captura pulso del sensor de Hum / Tmp

  distance = getDistance(duration);   // Lectura (invoca una subrutina)

  if (distance >= 200 || distance <= 0) {     // Verifica que esté en rango
    Serial.print("Fuera de rango (distancia = "); // Letreros...
    Serial.print(distance);           //
    Serial.print(", duracion = ");    //
    Serial.print(duration);           //
    Serial.println(")");              //
  }
  else {                        // Lectura dentro del rango
    Serial.print(distance);     // Impresión de la lectura
    Serial.println(" cms");     //
  }
  delay(500);                   // Retardo de tiempo para ir por otra lectura...
}
//------------------------------------------------------------------------------
//-----[ RUTINA para la Lectura de la Distancia ]-----
float getDistance(long dur) {       // Toma como dato ("dur") la distancia
  float t = dht.readTemperature();  // Lee la temperatura actual
  if (!(isnan(t))) {                // Si no se leyó un número...
    lasttemp = t;                   // ... recupera la última temperatura
  }
  // Cálculo de la distancia, considerando la perturbación ocasionada por
  // cambios en la temperatura del lugar donde se hace la medida:
  return (dur / 2) * ((331.5 + (0.6 * lasttemp)) / 10000);
}
//------------------------------------------------------------------------------
