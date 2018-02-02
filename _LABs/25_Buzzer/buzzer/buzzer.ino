//------------------------------------------------------------------------------
// Programa para Ejercitar un "Buzzer" (Zumbador)
//------------------------------------------------------------------------------
// Adaptado por: Sergio Fco. Hernández Machuca
// sfhm_clases@hotmail.com
//------------------------------------------------------------------------------

//-----[ Variables y Constantes ]-----
int potentiometerPin = 0;       // Entrada de un potenciómetro
int BuzPin = 11;                // Salida hacia un "Buzzer"
int potentiometerVal = 0;       // Valor leído de pin central del potenciómetro

//------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);          //  Velocidad de comunicación serial
}

//------------------------------------------------------------------------------
void loop() {
  // Lectura de un Voltaje variable, propuesto por el usuario:
  potentiometerVal = analogRead(potentiometerPin);     

  // Debido a que las terminales que generan señales PWN (moduladas en ancho 
  // de pulso) sólo aceptan valores de entre [0..255] y los valores de entradas
  // de terminales analógicas varían entre [0..1023], habrá que hacer un 
  // mapeo (traslado) entre ese conjunto de valores. Con la función "map" los
  // valores generados ( de entre [0..1023]) serán apropiadamente convertidos
  // a valores de entre [0..255]
  int mappedVal = map(potentiometerVal, 0, 1023, 0, 255);
  Serial.print(potentiometerVal);   // Valor leído del Potenciómetro
  Serial.print(" - ");              // Separador
  Serial.println(mappedVal);        // Valor correspondiente a señal PWM 
  analogWrite(BuzPin, mappedVal);   // Señal introducida al "Buzzer"
  delay(10);                        // Un pequeño retardo...
}
//------------------------------------------------------------------------------
