//------------------------------------------------------------------------------
// Programa para Ejercitar un Acelerómetro 3D asociado con LEDs
//
// ¡PRECAUCIÓN! Debe recordarse que el circuito ADXL335 emplea 3.3 Volts
// 
// Este código emplea, para la lectura de los valores de aceleración en los 
// ejes, las entradas analógicas de las siguientes terminales (pines):
//
// Eje X   -->   A(0)
// Eje Y   -->   A(1)
// Eje Z   -->   A(2)
//
// Se enciende el LED VERDE para bajo impacto y el LED ROJO para alto impacto.
//------------------------------------------------------------------------------

/**
Sketch uses 3d accelerometer on analog pins 0 (x), 1 (y), and 2 (z).
Turns on green LED for low impacts and red LED for higher impacts.
Thresholds for impacts defined below.

**REMEMBER TO USE 3.3v FOR ADXL335***

*/
// El umbral para el impacto se define a continuación:
#define REDTHRESH 10
#define GREENTHRESH 5
// Definición de las terminales para los LEDs:
#define REDLED 12
#define GREENLED 13

int x, y, z, oldx, oldy, oldz = 0;

void setup() {
//  Serial.begin(9600);         // Para el monitoreo de la ejecución
  pinMode(GREENLED, OUTPUT);
  pinMode(REDLED, OUTPUT);
}

void loop() {
  // Captura de los valores de x, y, z
  x = analogRead(0);
  y = analogRead(1);
  z = analogRead(2);
  
  // Cálculo de la diferencia de magnitud:
  int xchange = max(oldx, x) - min(oldx, x);
  int ychange = max(oldy, y) - min(oldy, y);
  int zchange = max(oldz, z) - min(oldz, z);

  // Apagado de los LEDs:
  digitalWrite(REDLED, LOW);
  digitalWrite(GREENLED, LOW);


  Serial.print("Aceleraciones: x, y, x: ");   // Para el monitoreo de la ejecución
  Serial.print(x, DEC);
  Serial.print(", ");
  Serial.print(y, DEC);
  Serial.print(", ");
  Serial.println(z, DEC);


  Serial.print("Cambios in x, y, z: ");
  Serial.print(xchange);
  Serial.print(", ");
  Serial.print(ychange);
  Serial.print(", ");
  Serial.println(zchange);  

  // Identificación del valor de cambio más grande de x, y, z
  int bigchange = max(xchange, max(ychange, zchange));

  if (bigchange > GREENTHRESH) {
    if (bigchange > REDTHRESH) {
      digitalWrite(REDLED, HIGH);
    } else {
      digitalWrite(GREENLED, HIGH);
    }
  }
  
  // Guardado de los valores de x, y, z para la próxima iteración:
  oldx = x;
  oldy = y;
  oldz = z;

  delay(100);
}
