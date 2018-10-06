#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);
String id1 = "";
void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
}

void loop() {
    id1 = "";
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {

    for (byte i = 0; i < mfrc522.uid.size; i++) {
      unsigned long id = (mfrc522.uid.uidByte);
      id1 = id1 + id;

      Serial.print(id, HEX);
      //Serial.print(" ");
    }
    Serial.print("\n");
    Serial.print(id1);    //to print id of Tag in serial monitor
    mfrc522.PICC_HaltA();
    Serial.print("\n");   //to give newline to serial output
  }
}


