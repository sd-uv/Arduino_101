//------------------------------------------------------------------------------
// Programa para pruebas de sensores de Impacto y  Acelerómetro ADXL335
//------------------------------------------------------------------------------

int out;                  // Variable

//------------------------------------------------------------------------------
void setup()
{
  Serial.begin(9600);     // Ajuste de la velocidad de la comunicación serial
}

//------------------------------------------------------------------------------
void loop()
{
  out = analogRead(0);        // Lectura del canal analógico "0"
  Serial.println(out, DEC);   // Impresión del valor leído  
  delay(100);                 // Espera para la próxima lectura
}
//------------------------------------------------------------------------------
