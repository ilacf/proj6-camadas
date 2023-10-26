int txPin = 2; // Pino de transmissão (TX)
int baudRate = 9600; // Velocidade de transmissão
int paridade;

void setup() {
  Serial.begin(baudRate);
  pinMode(txPin, OUTPUT);
  digitalWrite(txPin, HIGH);
}

void loop() {
  char characterToSend = "A";
  Serial.print("Transmição Iniciada!");
  digitalWrite(txPin, LOW);
  myClock(1666);
  for (int i = 0; i < 8; i++) {
    digitalWrite(txPin, characterToSend >> i & 1);
    if ((characterToSend >> i & 1) == 1) {
      paridade += 1;
    };
    myClock(1666);
  }
  if (paridade % 2 == 0) {
    Serial.println(" Par");
    digitalWrite(txPin, 0);
  } else {
    Serial.println(" Impar");
    digitalWrite(txPin, 1);
  }
  Serial.print("Caractere enviado com sucesso!");
  digitalWrite(txPin, HIGH);
  myClock(1666*1666);
}

void myClock(int clock) {
  for (int i = 0; i < clock ; i++){
      asm("NOP");
    }  
}