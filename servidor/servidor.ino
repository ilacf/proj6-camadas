int rxPin = 3; // Pino de recepção (RX)
int baudRate = 9600; // Velocidade de transmissão

int i;
int paridade;
int checkParidade;

char recebido;
bool esperando;
bool final = true;

void setup() {
  Serial.begin(baudRate);
  pinMode(rxPin, INPUT);
  Serial.println("Servidor Iniciado!");
}

void loop() {
  esperando = true;
  while (esperando) {
    esperando = digitalRead(rxPin); // Espera start bit
  }
  Serial.println("Recebendo Transmissão...");
  for (int i = 0; i < 2500 ; i++){
      asm("NOP");
    }
  i = 0;
  while (i < 8) {
    recebido |= digitalRead(rxPin) << i;
    for (int i = 0; i < 1666 ; i++){
      asm("NOP");
    }
    i += 1;
  }
  paridade = digitalRead(rxPin);
  for (int i = 0; i < 8; i++) {
    if ((recebido & (i << 1)) != 0) {
      checkParidade += 1;
    }
  }

  Serial.print("Bit de Paridade é: ");
  Serial.println(paridade);
  Serial.print("Quantidade de 1 foi: ");
  Serial.println(checkParidade);

  Serial.print("Caractere recebido foi: ");
  Serial.println(recebido);
  while (final) {
    for (int i = 0; i < 16000000000000  ; i++){
      asm("NOP");
    }
  }
}