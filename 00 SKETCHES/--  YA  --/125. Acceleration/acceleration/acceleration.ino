//------------------------------------------------------------------------------
// Programa para pruebas del Acelerómetro ADXL335
//------------------------------------------------------------------------------

int x, y, z;          // Variables

//------------------------------------------------------------------------------
void setup()
{
  Serial.begin(9600);      // Ajuste de la velocidad de comunicación serial
}

//------------------------------------------------------------------------------
void loop()
{
  x = analogRead(0);       // Lectura del pin 0 de entrada analógica
  y = analogRead(1);       // Lectura del pin 1 de entrada analógica
  z = analogRead(2);       // Lectura del pin 2 de entrada analógica
  Serial.print("Las Aceleraciones son: x, y, z: ");
  Serial.print(x, DEC);    // Imprime la aceleración en el eje X 
  Serial.print(" ");       // ... imprime un espacio entre los números...
  Serial.print(y, DEC);    // Imprime la aceleración en el eje Y 
  Serial.print(" ");       // ... imprime un espacio entre los números...
  Serial.println(z, DEC);  // Imprime la aceleración en el eje Z 
  delay(100);              // ... imprime un espacio entre los números...
}
//------------------------------------------------------------------------------
