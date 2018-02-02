//------------------------------------------------------------------------------
// Programa para ensayo del Seguidor de Línea (Breakout - Analog)
//------------------------------------------------------------------------------
int out;                    // Salida del Seguidor de Línea

//------------------------------------------------------------------------------
void setup()
{
  Serial.begin(9600);      // Ajuste de la velocidad de comunicación
}

//------------------------------------------------------------------------------
void loop()
{
  out = analogRead(0);        // Lectura del canal analógico "0"
  Serial.println(out, DEC);   // Impresión del valor leído
  delay(100);                 // Espera para la próxima lectura
}
//------------------------------------------------------------------------------

