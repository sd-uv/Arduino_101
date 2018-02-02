// Librerías que se requieren:
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  Serial.begin(9600);
  lcd.init();

  for (int i = 0; i < 5; i++)
  {
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
  }
  lcd.backlight();

  lcd.setCursor(3, 0);
  lcd.print("Hola Mundo");
  delay(2000);
  lcd.setCursor(3, 1);
  lcd.print("Desde AQUI");
  delay(1000);
  lcd.setCursor(0, 2);
  lcd.print("Desplegador 20 por 4");
  lcd.setCursor(0, 3);
  delay(2000);
  lcd.print("   ----------");
  delay(8000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Inicia Monitor");
  lcd.setCursor(0, 2);
  lcd.print("Escribe -> LCD");
}

void loop()
{
  {
    if (Serial.available()) {
      delay(100);
      lcd.clear();
      while (Serial.available() > 0) {
        lcd.write(Serial.read());
      }
    }
  }
}

