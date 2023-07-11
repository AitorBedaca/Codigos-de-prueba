#define EJE_X 62 //A8
#define EJE_Y 63 //A9
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
  if (botonPulsado == 1){
     Serial.print("\nBotón pulsado: ");
     Serial.print(botonPulsado);
  }
  
}
