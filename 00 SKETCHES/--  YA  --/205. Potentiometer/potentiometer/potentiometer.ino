//------------------------------------------------------------------------------
// Programa para la Lectura del Valor (Voltaje) proporcionado por un
// potenciómetro.
//
// El potenciómtero es un elemento mecánico configurado como una resistencia
// variable, la cual cambia su valor al mover un eje central. Con el cambio de
// posición del eje (perilla), se cambia la resistencia eléctrica entre dos
// puntos extremos. Habitualmente los puntos extremos se conectan a Voltajes
// (máximo y mínimo) a lo largo de los cuales se quiere tener una señal
// eléctrica (Voltaje o Corriente)
//------------------------------------------------------------------------------
//-----[ Variables y Constantes ]-----
int potentiometerPin = 0;     // Terminal para parte central del Potenciómetro
int ledPin = 11;              // Terminal para el LED
int potentiometerVal = 0;     // Valor leído (Voltaje) en la parte central del
// potenciómetro
//------------------------------------------------------------------------------
void setup()
{
  Serial.begin(9600);          //  Ajuste de la comunicación serial
}

//------------------------------------------------------------------------------
void loop()
{
  potentiometerVal = analogRead(potentiometerPin);  // Lectura

  // Se empleará la función "map" porque las terminales "PWM" (que generan
  // señales Moduladas por el Ancho de Pulsos) sólo aceptan valores de
  // 0 a 255. Las terminales que pueden leer valores analógicos generan valores
  // de entre 0 y 1023. Con la función "map" el rango [0..1023] es convertido
  // al valor correspondiente dentro del rango [0..255]. En realidad se aplica
  // la "regla de 3" para este cálculo, que hace para nosotros el compilador.

  // Encuentra a cuánto corresponde [0..255] de un valor leído entre [0..1023]:
  int mappedVal = map(potentiometerVal, 0, 1023, 0, 255);
  Serial.print(potentiometerVal);     // Imprime el valor del Potenciómetro
  Serial.print(" - ");                // ...separador...
  Serial.println(mappedVal);          // Imprime el valor del Voltaje
  analogWrite(ledPin, mappedVal);     // Ilumina al LED con el voltaje del Pot
  delay(10);                          // Espera un poquito para observar mejor...
}
//------------------------------------------------------------------------------
