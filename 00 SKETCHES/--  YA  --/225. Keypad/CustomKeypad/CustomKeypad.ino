//------------------------------------------------------------------------------
// Programa para implementar un Teclado con Interruptores en Matriz
//
// Permite el cambio de dimensión (hileras x columns) e identificación de
// teclas.
//------------------------------------------------------------------------------

//-----[ Bibliotecas y Archivos Auxiliares ]-----
// Se debe instalar la librería Keypad: http://playground.arduino.cc/Code/Keypad 
//
#include <Keypad.h>

//-----[ Constantes y Variables ]-----
const byte ROWS = 4; // Para 4 Hileras
const byte COLS = 4; // Para 4 Columnas 
// Definición de los símbolos en la serigrafía de los interruptores.
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[COLS] = {2, 3, 4, 5}; // Conección de los pines de las HILERAS.
byte colPins[ROWS] = {6, 7, 8, 9}; // Conección de los pines de las COLUMNAS.

// Inicializa una instancia de la clase NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

//------------------------------------------------------------------------------
void setup(){
  Serial.begin(9600); // Velocidad de la comunicación serial
}
//------------------------------------------------------------------------------
void loop(){
  char customKey = customKeypad.getKey(); // Lectura de una tecla oprimida
  
  if (customKey){               // Si se detectó una tecla oprimida...
    Serial.println(customKey);  // Imprímela en el monitor serial.
  }
}
//------------------------------------------------------------------------------
