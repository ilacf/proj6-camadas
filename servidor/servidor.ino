int rxPin = 3; // Pino de recepção (RX)
int baudRate = 9600; // Velocidade de transmissão
int paridade;
int checkParidade;
char recebido;
bool comecou == false;

void setup() {
  pinMode(rxPin, INPUT);
  Serial.begin(baudRate);
}

void loop() {
  Serial.print("Servidor Iniciado!");
  while (!comecou) {
    comecou = digitalRead(rxPin);
  }
  Serial.println("Recebendo Transmição...");
  myClock(2500);
  for (int i = 0; i < 8; i++) {
    recebido |= digitalRead(rxPin) << 1;
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
    Serial.println("Transmissão Concluida!");
  } else {
    Serial.println("ERRO!");
  }
  Serial.println(recebido);
  myClock(1666666);
}

void myClock(int clock) {
  for (int i = 0; i < clock*1000000 ;i++){
      asm("NOP");
    }
}