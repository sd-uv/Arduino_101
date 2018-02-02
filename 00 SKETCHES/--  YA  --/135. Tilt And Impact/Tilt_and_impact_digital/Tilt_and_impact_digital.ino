//------------------------------------------------------------------------------
// Programa para pruebas de sensores de Inclinación e Impacto
//------------------------------------------------------------------------------

int out;
#define tiltPin 12

//------------------------------------------------------------------------------
void setup(){
  Serial.begin(9600);       // Ajuste del canal serial
  pinMode(tiltPin, INPUT);  // Disposición de la terminal como ENTRADA
}
//------------------------------------------------------------------------------
void loop(){
  out = digitalRead(tiltPin); // Lectura de la entrada al canal analógico
  Serial.println(out, DEC);   // Resultado...
  delay(100);                 // Espera para la próxima lectura
}
//------------------------------------------------------------------------------

