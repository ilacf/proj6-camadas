int txPin = 2; // Pino de transmissão (TX)
int baudRate = 9600; // Velocidade de transmissão
int rodar = 0;

void setup() {
  pinMode(txPin, OUTPUT);
  Serial.begin(baudRate);
}

void loop() {
  if(rodar < 10){
    char characterToSend = 'A'; // Caractere a ser transmitido
    sendUARTChar(characterToSend);
    Serial.println("Bit enviado");
    delay(1000); // Espera 1 segundo antes de enviar o próximo caractere
  } else {
    return 0;
  }
}

// character >> i = character[i]

void sendUARTChar(char character) {
  int bit_paridade = 0;
  digitalWrite(txPin, LOW); // start bit (LOW)
  delayMicroseconds(1000000 / baudRate); // Aguarda o tempo de início
  for (int i = 0; i < 8; i++) {
    if ((character >> i & 1) == 1) {
      digitalWrite(txPin, HIGH);
      bit_paridade ++;
    } else {
      digitalWrite(txPin, LOW);
    }
    delayMicroseconds(1000000 / baudRate); // Aguarda o tempo de cada bit
  }

  if(bit_paridade/2 == 0){
    digitalWrite(txPin, LOW);
  } else {
    digitalWrite(txPin, HIGH);
  }

  digitalWrite(txPin, HIGH); // stop bit (HIGH)
  delayMicroseconds(1000000 / baudRate); // Aguarda o tempo de parada

  rodar++;
}