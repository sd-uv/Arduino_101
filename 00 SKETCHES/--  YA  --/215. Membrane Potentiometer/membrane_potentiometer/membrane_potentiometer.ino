//------------------------------------------------------------------------------
// Programa para pruebas de un Potenciómetro de Membrana
//------------------------------------------------------------------------------

// No requerimos variables o constantes

//------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);       // Inicialización de la comunicación serial
}

//------------------------------------------------------------------------------
void loop() {
  int sensorValue = analogRead(A0); // Lectura de la entrada analógica en "A0"
  // Conversión de la lectura analógica [0..1023] a un Voltaje [0..5]:
  float voltage = sensorValue * (5.0 / 1023.0); //
  Serial.println(voltage);          // Impresión del valor Voltaje leído 
}
//------------------------------------------------------------------------------
