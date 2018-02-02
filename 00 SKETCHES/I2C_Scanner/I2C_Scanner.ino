// I2C Scanner
// Written by Nick Gammon
// Date: 20th April 2011

#include <Wire.h>

void setup() {
  Serial.begin (115200);

  // Para versión Leonardo...
  while (!Serial)
  {
  }

  Serial.println ();
  Serial.println ("Rastreador de direcciones I2C");
  Serial.println ("..... Verificando .....");
  byte count = 0;

  Wire.begin();
  for (byte i = 8; i < 120; i++)
  {
    Wire.beginTransmission (i);
    if (Wire.endTransmission () == 0)
    {
      Serial.print ("Dirección Encontrada: ");
      Serial.print (i, DEC);
      Serial.print (" (0x");
      Serial.print (i, HEX);
      Serial.println (")");
      count++;
      delay (1);          // ¿Se requiere?
    }                   // Fin de una respuesta buena.
  }                       // Fin del ciclo de búsqueda.

  Serial.println (".Listo.");
  Serial.print ("Encontrado(s) ");
  Serial.print (count, DEC);
  Serial.println (" dispositivos(s).");
}                         // Fin de los ajustes.

void loop()
{
}

