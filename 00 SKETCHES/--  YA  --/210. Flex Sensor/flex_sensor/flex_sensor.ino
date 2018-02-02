//------------------------------------------------------------------------------
// Programa para Ejercitar la lectura de Sensores de Flexión
//
// Las terminales del sensor se colocan de modo tal que la resistencia (que 
// cambia en función de la flexión de esta hoja) genere un cambio de voltaje
// que leeremos en una terminal analógica de nuestro sistema.
// Emplearemos el concepto de "Divisor de Voltaje".
//
//------------------------------------------------------------------------------

// No requerimos variables o constantes

//------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);           // Velocidad de comunicación del puerto serial
}
//------------------------------------------------------------------------------
void loop() {
  int sensorValue = analogRead(A0); // Lectura del voltaje en entrada analógica
  // Conversión de la lectura analógica [0..1023] a un voltaje correspondiente
  // a una variación de entre [0..5]:
  float voltage = sensorValue * (5.0 / 1023.0); // Valor del Voltaje
  Serial.println(voltage);          // Impresión del Valor leído...
}
//------------------------------------------------------------------------------
