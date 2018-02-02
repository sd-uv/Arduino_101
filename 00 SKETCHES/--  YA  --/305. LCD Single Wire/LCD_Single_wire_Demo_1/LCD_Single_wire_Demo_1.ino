//------------------------------------------------------------------------------
// Programa para Ejercitar una Pantalla de Cristal Líquido (LCD) usando
// una interface I2C
//
// Para este ensayo se usa un adaptador I2C basado en CI PDF
//------------------------------------------------------------------------------

//-----[ Bibliotecas ]-----
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Creación de una instancia de la clase LCD-I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);
//------------------------------------------------------------------------------
void setup() {
  lcd.begin(16, 2);             // Puesta a funcionar de la LCD
  lcd.backlight();              // Encendido de la luz de fondo
  lcd.setCursor(0, 0);          // Cursor en la posición de "Casa"
  lcd.print("Hola Mundo");      // Letrero
  lcd.setCursor(0, 1);          // En otra línea
  lcd.print("Hilera Num: ");    // Imprime ...
  lcd.setCursor(12, 1);         // Posiciona cursor ...
  lcd.print("2");               // 
}
//------------------------------------------------------------------------------
void loop() {

}
