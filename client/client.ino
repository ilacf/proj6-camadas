char txPin  = 2;
int paridade;
char characterToSend = 'K';
bool final = true;

void setup() {
  Serial.begin(9600);
  pinMode(txPin, OUTPUT);
  digitalWrite(txPin, HIGH);
}

void loop() {
  Serial.println("Transmissão Iniciada");
  digitalWrite(txPin, LOW);
  for (int i = 0; i < 1666 ;i++){
    asm("NOP");
  }  
  for (int i = 0; i < 8; i++) {
    digitalWrite(txPin, characterToSend >> i & 1);
    if ((characterToSend >> i & 1) == 1){
      paridade += 1;
    }
    for (int i = 0; i < 1666 ;i++){
      asm("NOP");
    }  
  }
  if (paridade % 2 == 0){
    Serial.println("Par");
    digitalWrite(txPin, 0);
  } else {
    Serial.println("Impar");
    digitalWrite(txPin, 1);
  }
  while(final){
    Serial.println("Transmissão Concluida");
    digitalWrite(txPin, HIGH);
    for (int i = 0; i < 16000000000000 ;i++){
      asm("NOP");
    }  
  }
}