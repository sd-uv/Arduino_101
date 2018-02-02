// Ejemplo de uso del módulo de Reloj de Tiempo Real (RTC)
//
// Emplea las siguientes conexiones:
//
// SCL  --> A5
// SDA  --> A4
// GND  --> GND
// Vcc  --> +5V
//------------------------------------------------------------------------------
// Adaptado por: Sergio Fco. Hernández Machuca
// sfhm_clases@hotmail.com
//------------------------------------------------------------------------------

// Librerías necesarias:

#include <Wire.h>
#include "RTClib.h"

// Definición de resursos que se emplean (Canal I2C):
const int outputPin = LED_BUILTIN;
bool state = false;

// Instancia de un RTC, especificando el tipo en particular:
// RTC_DS1307 rtc;
RTC_DS3231 rtc;

void setup() {
  Serial.begin(9600);
  delay(1000);
  
  if (!rtc.begin()) {
    Serial.println(F("No puedo encontrar al RTC"));
    while (1);
  }
  
  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

// Comprobar si está programado el encendido
bool isScheduledON(DateTime date)
{
  int weekDay = date.dayOfTheWeek();
  float hours = date.hour() + date.minute() / 60.0;
  
  // De 12:53 a 12:58 y de 21:00 a 23:00
  // -> bool hourCondition = (hours > 13.02 && hours < 13.05) || (hours > 21.00 && hours < 23.00);

   bool hourCondition = (hours > 12.20 && hours < 13.05) || (hours > 21.00 && hours < 23.00);

  // Martes, Sabado o Domingo
  bool dayCondition = (weekDay == 3 || weekDay == 6 || weekDay == 0); 
  if (hourCondition && dayCondition)
  {
    return true;
  }
  return false;
}

void loop() {
  DateTime now = rtc.now();

  if (state == false && isScheduledON(now)) // Apagado y debería estar encendido
  {
    digitalWrite(outputPin, HIGH);
    state = true;
    Serial.print("Activado");
  }
  else if (state == true && !isScheduledON(now)) // Encendido y deberia estar apagado
  {
    digitalWrite(outputPin, LOW);
    state = false;
    Serial.print("Desactivar");
  }

  delay(3000);
}
