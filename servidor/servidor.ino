int rxPin = 3; // Pino de recepção (RX)
int baudRate = 9600; // Velocidade de transmissão
int rodar = 1;

void setup() {
  pinMode(rxPin, INPUT);
  Serial.begin(baudRate);
}

void loop() {
  if(rodar == 1){
    char receivedCharacter = receiveUARTChar();
    if (receivedCharacter != 0) {
      Serial.print("Caractere recebido: ");
      Serial.println(receivedCharacter);
    }
  } else {
    return 0;
  }

}

char receiveUARTChar() {
  int bit_paridade = 0;
  // recebendo start bit
  int start_bit = digitalRead(rxPin);
  Serial.print(start_bit);
  int receivedCharacter = 0;
  delayMicroseconds(1000000 / baudRate / 2); // Meio tempo de início
  if(start_bit == LOW){
    for (int i = 0; i < 8; i++) {
      if(digitalRead(rxPin) == 1){
        bit_paridade ++;
      }
      int receivedCharacter = ((digitalRead(rxPin) << i) & 1);
      delayMicroseconds(1000000 / baudRate); // Aguarda o tempo de cada bit
    }
    int bit_paridade_receb = (digitalRead(rxPin));
    delayMicroseconds(1000000 / baudRate / 2); // Meio tempo de parada

    if(bit_paridade/2 == 0){
      return receivedCharacter;
    } else {
      return 0; // indica que houve erro de paridade
    }
  }
  rodar = 0;
}