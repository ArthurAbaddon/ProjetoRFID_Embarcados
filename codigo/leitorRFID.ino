#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN D8
#define RST_PIN D0
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

struct sCartaoRFID{
  byte id;
  byte codigo[4];
  char nome[20];
};

#define QUANTIDADE_CHAVES 2
sCartaoRFID lista_chaves[QUANTIDADE_CHAVES] = {{1, {0x41, 0x19, 0xF9, 0x20}, "Cartao 1"},
                                               {2, {0x41, 0x1C, 0xE2, 0x20}, "Cartao 2"}
                                              };

void init_rfid()
{
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522
  Serial.println();
  Serial.print(F("Reader :"));
  rfid.PCD_DumpVersionToSerial();
  Serial.println();
}

void imprimir_lista_chaves()
{
  Serial.println("Lista de chaves cadastradas");
  for(byte i=0; i < QUANTIDADE_CHAVES; i++)
  {
    sCartaoRFID cartao = lista_chaves[i];
    Serial.println(cartao.nome);
  }
  Serial.println("----------------------");
}

int buscar_chave(byte* cartao_lido){
  int ret = -1;
  for(byte i=0; i < QUANTIDADE_CHAVES; i++)
  {
      sCartaoRFID cartao = lista_chaves[i];
      if (lista_chaves[i].codigo[0] == cartao_lido[0] &&
          lista_chaves[i].codigo[1] == cartao_lido[1] &&
          lista_chaves[i].codigo[2] == cartao_lido[2] &&
          lista_chaves[i].codigo[3] == cartao_lido[3]) 
      {
        Serial.println("ACHOU!");
        ret = i;
        break;
      }
  }
  return ret;
}


char* ler_cartao(){
  if ( ! rfid.PICC_IsNewCardPresent())
      return NULL;
  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
      return NULL;

  //Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  //Serial.println(rfid.PICC_GetTypeName(piccType));
  
  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
          piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
          piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
      Serial.println(F("Your tag is not of type MIFARE Classic."));
      return NULL;
  }
  rfid.PICC_HaltA();
  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
  int index = buscar_chave(rfid.uid.uidByte);
  if(index < 0)
  {
    Serial.println("Cartao nao identificado.");
    return NULL;
  }

  sCartaoRFID cartao = lista_chaves[index];
  Serial.println(cartao.nome);

  return (char*)(cartao.nome);
  
  //else Serial.println(F("Card read previously."));
  // Halt PICC
  
  
}
