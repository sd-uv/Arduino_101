// Programa de prueba para el ensayo de sensores de Humedad / Temperatura.

#include <DHT.h>

#define DHTPIN 2     // Terminal (o pin) digital al que se conectará el sensor.

// Se le quita el comentario al tipo de sensor que se empleará.
//#define DHTTYPE DHT11   // DHT 11 
  #define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Activación del elemento sensor, identificación de sus recursos y nombre:
DHT dht(DHTPIN, DHTTYPE);

// Ajustes:
void setup() {
  // Ajuste de la comunicación.
  Serial.begin(9600);
  // Impresión del Título  
  Serial.println("Prueba de un DHT");   
  // Inicio de las funciones del sensor empleado, esto es obligatorio.
  dht.begin();
}

// Ejecución cíclica eterna...
void loop() {
  // La lectura de la temperatura o humedad toma cerca de 250 milisegundos.
  // ¡Algunos sensores (económicos) pueden tardar hasta 2 segundos!
  float h = dht.readHumidity();     // Lectura de la humedad  
  float t = dht.readTemperature();  // Lectura de la temperatura

  // Revisar si el dato es válido. 
  // Si lo leído se identifica como NaN (Not a Number), entonces algo está mal.
  if (isnan(t) || isnan(h)) {
    Serial.println("Se FALLO en la lectura del DHT");
  } else {
    Serial.print("Humedad: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperatura: ");
    Serial.print(t);
    Serial.println(" *C");
  }
    delay(500);    // Inserción de un retardo de 5 segundos entre lecturas.
}

