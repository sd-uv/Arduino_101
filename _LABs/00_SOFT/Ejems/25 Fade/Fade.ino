/*
 Desvanecimiento
 
 Este ejemplo muestra como desvanecer la iluminación en un LED colocado en la
 terminal "9" empleando la función analogWrite().
 
 */
//------------------------------------------------------------------------------
// Adaptado por: Sergio Fco. Hernández Machuca
// sfhm_clases@hotmail.com
//------------------------------------------------------------------------------

int led = 9;           // La terminal en la que se coloca el LED.
int brightness = 0;    // Cuánta brillantez tendrá el LED.
int fadeAmount = 15;    // Cada cuántos puntos se desvanecerá la iluminación.

// Esta rutina de ajuste se ejecuta una sola vez cuando se oprime "Reset":
void setup()  { 
  pinMode(led, OUTPUT);  // Inicializa el Pin Digital como "salida".
} 

// Esta rutina en lazo se ejecuta una y otra vez, por siempre:
void loop()  {
  // Ajusta la brillantez de la terminal "9".
  analogWrite(led, brightness); 

  // Cambia la brillantez para la próxima vez que pases por aquí...
  brightness = brightness + fadeAmount;

  // Si se llegó al tope (fin del ciclo)...
  // ...invierte la dirección del desvanecimiento
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ; 
  }     
  // Espera por 20 milliseconds para observar el efecto en la iluminación.    
  delay(20);                            
}

