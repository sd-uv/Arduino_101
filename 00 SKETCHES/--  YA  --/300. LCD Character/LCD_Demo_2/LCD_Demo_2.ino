//------------------------------------------------------------------------------
// Programa para Ejercitar una Pantalla de Cristal Líquido (LCD)
//
// En este programa se muestra el uso básico de una pantalla LCD de 16x2 en
// conjunto con un sensor de Humedad y Temperatura
//
//  El circuito emplea las siguientes conexiones:
// LCD RS     --> pin digital 12
// LCD Enable --> pin digital 11
// LCD D4     --> pin digital 5
// LCD D5     --> pin digital 4
// LCD D6     --> pin digital 3
// LCD D7     --> pin digital 2
// LCD R/W    --> pin de tierra (0 volts)
// Una resistencia de 10K, terminales extremas entre +5 Volts y 0 Volts (tierra)
//  terminal intermedia al pin 3 del LCD (LCD VO)
//
//------------------------------------------------------------------------------
//----[ Librerías que se DEBEN Incluir ]-----
// Se DEBE instalar la librería "Adafruit Unified Sensor" [https://github.com/adafruit/Adafruit_Sensor]
#include <LiquidCrystal.h>
#include <DHT.h>

#define DHTPIN 7          // Terminales que estarán conectadas al
#define DHTTYPE DHT22     // dispositivo DHT 22  (AM2302)

DHT dht(DHTPIN, DHTTYPE); // Creación de una instancia del sensor

// Instancia de la LCD, con los números de pines empleados:
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
//------------------------------------------------------------------------------
void setup() {
  lcd.begin(16, 2);       // Ajuste del número de Columnas e Hileras de la LCD
  lcd.print("Prueba de DHT");  // Impresión de un mensaje
  dht.begin();            // Puesta a punto del sensor (Obligatorio)
}
//------------------------------------------------------------------------------
void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Revisión de la lectura del sensor, si lo recibido fuera distinto a un 
  // (NaN, not a number), entonces ¡Algo está mal!!
  if (isnan(t) || isnan(h)) {
    lcd.clear();                    // Limpia la pantalla
    lcd.setCursor(0, 0);            // Posiciona el cursor
    lcd.print("Error en Lectura");  // Imprime letrero
    lcd.setCursor(0, 1);            // Posiciona en la segunda línea   
    lcd.print("del DHT");           // Imprime otro letrero
  // Después de interrogar al sensor, se recibió un número:
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Hum: ");
    lcd.print(h);
    lcd.print(" %");
    lcd.setCursor(0, 1);
    lcd.print("Temp: ");
    lcd.print(t);
    lcd.print(" *C");
  }
}
