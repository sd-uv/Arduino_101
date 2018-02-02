//------------------------------------------------------------------------------
// Programa para Ejercitar una Pantalla de Cristal Líquido (LCD)
//
// En este sketch se muestra el uso básico de una pantalla LCD de 16x2, es decir
// de 16 caracteres con 2 líneas. Estos dispositivos genéricamente son
// compatibles con el manejador Hitachi HD44780. El dispositivo típico tiene una
// interface de 16 pines. Este ensayo imprime un letrero de bienvenidad y
// despliega el tiempo.
//
//  El circuito emplea las siguientes conexiones:
// LCD RS     --> pin digital 12
// LCD Enable --> pin digital 11
// LCD D4     --> pin digital 5
// LCD D5     --> pin digital 4
// LCD D6     --> pin digital 3
// LCD D7     --> pin digital 2
// LCD R/W    --> pin de tierra (0 volts)
// Una resistencia de 10K, terminales extremas entre +5 Volts y 0 Volts (tierra)
//  terminal intermedia al pin 3 del LCD (LCD VO)
//
//------------------------------------------------------------------------------

//----[ Librerías que se DEBEN Incluir ]-----
#include <LiquidCrystal.h>

// Iniciación del elemento según la librería, con los números de pines:
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//------------------------------------------------------------------------------
void setup() {
  // Ajuste del número de COLUMNAS e HILERAS de la LCD:
  lcd.begin(16, 2);
  // Impresión de un mensaje en la LCD:
  lcd.print("Hola Mundo");
}
//------------------------------------------------------------------------------
void loop() {
  // Ajuste del cursor a la Hilero 0, Linea 1
  // Nota: La línea 1 es la segunda hilera, dado que el conteo inicia en 0.
  lcd.setCursor(0, 1);
  // Imprime el número de segundos que han ocurrido desde la última señal de
  // "Reset":
  lcd.print(millis() / 1000);
}
//------------------------------------------------------------------------------
