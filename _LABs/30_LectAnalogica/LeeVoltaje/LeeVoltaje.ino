//------------------------------------------------------------------------------
// Programa para la lectura de un Voltaje Analógico
//
// Se lee la entrada de la terminal analógica "0", se convierte a Voltaje
// e imprime el resultado en el monitor serial.
// Se conecta la terminal central de un potenciómetro a la terminal (pin) "A0",
// y las terminales externas del potenciómetro se conectan a los puntos
// de + 5 Volts y a 0 Volts (Tierra).
//------------------------------------------------------------------------------
// Adaptado por: Sergio Fco. Hernández Machuca
// sfhm_clases@hotmail.com
//------------------------------------------------------------------------------

// No se requiere declarar constantes ni variables.

//------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);       // Inicializa la comunicación serial a 9,600 bauds
}

//------------------------------------------------------------------------------
void loop() {
  int sensorValue = analogRead(A0); // Lectura ddel voltaje presente en "A0"
  // Se coonvierte la lectura analógica (la cual varía de 0 a 1023) al rango
  // de voltaje presente en la entrada (de 0 a 5 volts).
  // Valor (0 - 1023) convertido a voltaje (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  // Impresión del valor leído:
  Serial.println(voltage);
}
//------------------------------------------------------------------------------
