//------------------------------------------------------------------------------
// Programa para implementar un Teclado que emplea una sola línea de entrada
//
// Utiliza la entrada analógica en "A0", la cual está asociada a un arreglo
// de interruptores asociado con una red de resistencias. El arreglo de
// interruptores y resistencias genera un voltaje distinto para la acción
// (estado de oprimido) de cada una de las teclas.
//------------------------------------------------------------------------------

//-----[ Constantes y Variables ]-----
char* keypressed = 0;   // Aloja el valor de la tecla oprimida
int keyboardPin = 0;    // Pin de entrada analógica asociada con el teclado
int keyboardValue = 0;  // Valor leído del teclado

//------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);   // Velocidad de comunicación serial
}

//------------------------------------------------------------------------------
void loop() {
  keyboardValue = analogRead(A0);  // Lectura del teclado (un valor [0..1023]

  while (keyboardValue < 5) {      
    keyboardValue = analogRead(A0); // ¿Hay una Tecla Oprimida?
    delay(50);                      // ...NO, continúa aquí...
  }
  readkeyboard(); // Ya se oprimió una tecla, obtén valor ("keypressed", [0..9]
}
//------------------------------------------------------------------------------

//-----[ RUTINA para la Lectura de la Tecla Oprimida ]-----
void readkeyboard() {
  keyboardValue = analogRead((A0)); // Lectura de entrada (A0) [0..1023]
  Serial.print("Valor Leído (A0): ");     // Valor leído
  Serial.println( keyboardValue);         //
  //   if (keyboardValue <25){keypressed = 0;}
  // TABLA de VALORES CALCULADOS para cada TECLA OPRIMIDA
  if ((keyboardValue > 842) && (keyboardValue < 845)) {
    keypressed = "1";
  }
  if ((keyboardValue > 735) && (keyboardValue < 738)) {
    keypressed = "2";
  }
  if ((keyboardValue > 639) && (keyboardValue < 642)) {
    keypressed = "3";
  }
  if ((keyboardValue > 516) && (keyboardValue < 518)) {
    keypressed = "4";
  }
  if ((keyboardValue > 474) && (keyboardValue < 476)) {
    keypressed = "5";
  }
  if ((keyboardValue > 432) && (keyboardValue < 435)) {
    keypressed = "6";
  }
  if ((keyboardValue > 349) && (keyboardValue < 351)) {
    keypressed = "7";
  }
  if ((keyboardValue > 329) && (keyboardValue < 331)) {
    keypressed = "8";
  }
  if ((keyboardValue > 309) && (keyboardValue < 311)) {
    keypressed = "9";
  }
  if ((keyboardValue > 257) && (keyboardValue < 259)) {
    keypressed = "0";
  }
  if ((keyboardValue > 269) && (keyboardValue < 272)) {
    keypressed = "*";
  }
  if ((keyboardValue >= 245) && (keyboardValue < 247)) {
    keypressed = "#";
  }
  if ((keyboardValue > 598) && (keyboardValue < 600)) {
    keypressed = "A";
  }
  if ((keyboardValue > 416) && (keyboardValue < 419)) {
    keypressed = "B";
  }
  if ((keyboardValue > 303) && (keyboardValue < 305)) {
    keypressed = "C";
  }
  if ((keyboardValue > 242) && (keyboardValue < 245)) {
    keypressed = "D";
  }
  if (keyboardValue > 938) {
    keypressed = 0;
  }
  // NOTA: Los valores empleados anteriormente corresponden a la 
  // mitad de los obtenidos en pruebas previas.
  // Se sugiere realizar una calibración minuciosa antes de emplear este
  // esquema.

  // Antes de continuar espera hasta que se deje de oprimir la tecla:
  while (keyboardValue > 25) {
    delay (100);
    keyboardValue = analogRead((A0));
  }

  Serial.println(keypressed);      // Impresión del Código de la Tecla oprimida
  delay(1000);                     // Espera para detectar otra tecla oprimida
}
// FIN de la rutina keyboard
//------------------------------------------------------------------------------



