int F1 = 5;
int R1 = 9;
int M1 = 4;

int F2 = 6;
int R2 = 10;
int M2 = 7;

int pot1Pin = 0;
int pot2Pin = 1;

void setup() {
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
}

void loop() {
  int pot1Val = analogRead(pot1Pin);
  int pot2Val = analogRead(pot2Pin);
  move_motors(pot1Val, pot2Val);
}

void move_motors(int pot1Val, int pot2Val) {  
  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  
  if (pot1Val < 512) {
    // attack! (forwards)
    int value = map(pot1Val, 512, 0, 0, 255);
    analogWrite(F1, value);
  } else {
    // retreat! (backwards)
    int value = map(pot1Val-512, 0, 512, 0, 255);
    analogWrite(R1, value);
  }
  
  if (pot2Val < 512) {
    // attack! (forwards)
    int value = map(pot2Val, 512, 0, 0, 255);
    analogWrite(F2, value);
  } else {
    // retreat! (backwards)
    int value = map(pot2Val-512, 0, 512, 0, 255);
    analogWrite(R2, value);
  }
}

