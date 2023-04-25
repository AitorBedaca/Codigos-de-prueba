#define EJE_X 0
#define EJE_Y 1
#define BOTON 2

void setup() {
  Serial.begin(9600);
  // Será de tipo entrada
  pinMode(BOTON, INPUT_PULLUP);
}

void loop() {
  int valorX = analogRead(EJE_X),
      valorY = analogRead(EJE_Y),
      botonPulsado = digitalRead(BOTON);
  Serial.print("\nValor X: ");
  Serial.print(valorX);
  Serial.print("\nValor Y: ");
  Serial.print(valorY);
  Serial.print("\nBotón pulsado: ");
  Serial.print(botonPulsado);
  delay(100);
}
