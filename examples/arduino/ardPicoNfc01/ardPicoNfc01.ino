//https://forum.arduino.cc/t/using-a-rfid-rc522-board-with-an-rp2040-chip-and-the-arduino-ide/1077813/2

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN  27
#define RST_PIN 6
#define NFC_CS  26
//#define SS_PIN 1
//#define RST_PIN 0

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  Serial.println("start")

  pinMode(NFC_CS, OUTPUT); //chip select, to selectably enable 
                            //one of multiple NFC (or sister SPI devices) 
  digitalWrite(NFC_CS, LOW));

  SPI.begin(); // init SPI bus
  rfid.PCD_Init(); // init MFRC522

  Serial.println("Tap RFID/NFC Tag on reader");
}

void loop() {
  if (rfid.PICC_IsNewCardPresent()) { // new tag is available
    if (rfid.PICC_ReadCardSerial()) { // NUID has been readed
      MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
      //Serial.print("RFID/NFC Tag Type: ");
      //Serial.println(rfid.PICC_GetTypeName(piccType));

      // print NUID in Serial Monitor in the hex format
      Serial.print("UID:");
      for (int i = 0; i < rfid.uid.size; i++) {
        Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(rfid.uid.uidByte[i], HEX);
      }
      Serial.println();

      rfid.PICC_HaltA(); // halt PICC
      rfid.PCD_StopCrypto1(); // stop encryption on PCD
    }
  }
}