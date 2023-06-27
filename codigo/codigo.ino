
//MFRC522::MIFARE_Key key;
//
//// Init array that will store new NUID
//byte nuidPICC[4];
void setup() {
  Serial.begin(115200);
  init_rfid();
//  for (byte i = 0; i < 6; i++) {
//      key.keyByte[i] = 0xFF;
//  }
//  Serial.println();
//  Serial.println(F("This code scan the MIFARE Classic NUID."));
//  Serial.print(F("Using the following key:"));
//  printHex(key.keyByte, MFRC522::MF_KEY_SIZE);
  imprimir_lista_chaves();
}
void loop() {
  char* nome_chave = ler_cartao();
  if(nome_chave != NULL)
  {
    Serial.println(nome_chave);
  }
}
/**
    Helper routine to dump a byte array as hex values to Serial.
*/
void printHex(byte *buffer, byte bufferSize) {
  byte i;
  for (i = 0; i < bufferSize; i++) {
      Serial.print(buffer[i] < 0x10 ? " 0" : " ");
      Serial.print(buffer[i], HEX);
  }
}
/**
    Helper routine to dump a byte array as dec values to Serial.
*/
void printDec(byte *buffer, byte bufferSize) {
  byte i;
  for (i = 0; i < bufferSize; i++) {
      Serial.print(buffer[i] < 0x10 ? " 0" : " ");
      Serial.print(buffer[i], DEC);
  }
}
