int rxPin = 3; // Pino de recepção (RX)
int baudRate = 9600; // Velocidade de transmissão
int paridade;
int checkParidade;
char recebido;
bool esperando;

void setup() {
  Serial.begin(baudRate);
  pinMode(rxPin, INPUT);
}

void loop() {
  esperando = true;
  Serial.print("Servidor Iniciado!");
  while (esperando) {
    esperando = digitalRead(rxPin); // Espera start bit
  }
  Serial.println("Recebendo Transmição...");
  myClock(2500);
  for (int i = 0; i < 8; i++) {
    recebido |= digitalRead(rxPin) << i;
    myClock(1666);
  }
  paridade = digitalRead(rxPin);
  for (int i = 0; i < 8; i++) {
    if ((recebido & (i << 1)) != 0) {
      checkParidade += 1;
    }
  }
  Serial.print("Bit de Paridade é: ");
  Serial.print(paridade);
  Serial.print("Quantidade de 1 foi: ");
  Serial.print(checkParidade);

  if ((checkParidade % 2 != 0 & paridade == 1) || (checkParidade % 2 == 0 & paridade == 0)) {
    Serial.println(" Transmissão Concluida!");
  } else {
    Serial.println(" ERRO!");
  }
  Serial.println(recebido);
  myClock(1666*1666);
}

void myClock(int clock) {
  for (int i = 0; i < clock ; i++){
      asm("NOP");
    }
}