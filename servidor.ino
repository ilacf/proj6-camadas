const int rxPin = 3; // Pino de recepção (RX)
const int baudRate = 9600; // Velocidade de transmissão

void setup() {
  pinMode(rxPin, INPUT);
  Serial.begin(baudRate);
}

void loop() {
  char receivedCharacter = receiveUARTChar();
  if (receivedCharacter != 0) {
    Serial.print("Caractere recebido: ");
    Serial.println(receivedCharacter);
  }
}

char receiveUARTChar() {
  int bit_paridade = 0;
    // recebendo start bit
    start_bit = digitalRead(rxPin);
    delayMicroseconds(1000000 / baudRate / 2); // Meio tempo de início
    if(start_bit == LOW){
      for (int i = 0; i < 8; i++) {
        if(digitalRead(rxPin) == 1){
          bit_paridade ++;
        }
        receivedCharacter |= (digitalRead(rxPin) << i);
        delayMicroseconds(1000000 / baudRate); // Aguarda o tempo de cada bit
      }
      bit_paridade_receb = (digitalRead(rxPin);
      delayMicroseconds(1000000 / baudRate / 2); // Meio tempo de parada

      if(bit_paridade/2 == 0){
        return receivedCharacter;
      } else {
        return 0; // indica que houve erro de paridade
      }
    }
}