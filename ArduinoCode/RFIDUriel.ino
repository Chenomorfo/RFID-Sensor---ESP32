#include <Arduino.h>

#pragma region RFID Components

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 21
#define RST_PIN 22
#define BUZZER_PIN 2

MFRC522 rfid(SS_PIN, RST_PIN);  // Instance of the class

MFRC522::MIFARE_Key key;

// Init array that will store new NUID
byte nuidPICC[4];
#pragma endregion

#pragma region HTTP Components

#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>

#define USE_SERIAL Serial

WiFiMulti wifiMulti;

#pragma endregion



void setup() {
  Serial.begin(9600);

  //HTTP
  for (uint8_t t = 4; t > 0; t--) {
    USE_SERIAL.printf("[SETUP] Espere %d...\n", t);
    USE_SERIAL.flush();
    delay(1000);
  }

  wifiMulti.addAP("CHENO", "123456789");

  //RFID
  SPI.begin();      // Init SPI bus
  rfid.PCD_Init();  // Init MFRC522

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  Serial.println(F("This code scan the MIFARE Classsic NUID."));
  Serial.print(F("Using the following key:"));
  printHex(key.keyByte, MFRC522::MF_KEY_SIZE);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {

  if ((wifiMulti.run() != WL_CONNECTED)) {
    Serial.print(F("Conection Refused...."));
    delay(1500);
    return;
  }

  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if (!rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if (!rfid.PICC_ReadCardSerial())
    return;

  EntryPass();
  Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));

  // if (IsNewCard(nuidPICC, rfid.uid.uidByte)) {
  Serial.println(F("A new card has been detected."));

  // Store NUID into nuidPICC array
  for (byte i = 0; i < 4; i++) {
    nuidPICC[i] = rfid.uid.uidByte[i];
  }
  String data = RFIDHEX(rfid.uid.uidByte, rfid.uid.size);
  Serial.println(F("The NUID tag is:"));
  Serial.print(F("In hex: "));
  Serial.print(data);
  Serial.println();

  POST_RFID(data);

  //} else Serial.println(F("Card read previously."));

  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}
