#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();

  Serial.println("RFID UID Scanner Ready...");
  Serial.println("Scan your RFID tag...");
}

void loop() {

  // Look for new card
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  Serial.print("UID Tag : ");

  // Print UID
  for (byte i = 0; i < mfrc522.uid.size; i++) {

    if (mfrc522.uid.uidByte[i] < 0x10) {
      Serial.print("0");
    }

    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }

  Serial.println();
  Serial.println("-----------------------");

  delay(1000);   // Small delay to avoid multiple reads
}
