//------------------------------------------------------------------------------
// Programa para Calcular el valor de comparación para Tecla Oprimida
// en un teclado de una sola conexión a una entrada Analógica.
//------------------------------------------------------------------------------

//-----[ Constantes y Variables]-----
String keys = "123A456B789C*0#D";   // Valores Simbólicos de las teclas
int key;                            // Tecla oprimida
boolean key_lockout = false;        // Estado (verdadero / falso) del teclado
//------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);       // Velocidad de comunicación serial
}
//------------------------------------------------------------------------------
void loop() {
  key = getKeypad();
  if (key != -1)
    Serial.println(keys[key]);
  delay(10);
}
//------------------------------------------------------------------------------
//-----[ RUTINA para Obtención de la Tecla Oprimida ]-----
int getKeypad() {
                          //  Serial.println(analogRead(A0));
  int ret = -1;

  if (analogRead(A0) == 0)
    key_lockout = false;
  else if (!key_lockout) {
    delay(20);
    Serial.println(analogRead(A0));
    ret = 15 - (log((analogRead(A0) - 183.9) / 58.24) / 0.1623) + 0.5;
    key_lockout = true;
  }
  return ret;
}
//------------------------------------------------------------------------------
