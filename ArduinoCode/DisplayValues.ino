/**
 * Helper routine to dump a byte array as hex values to Serial. 
 */
void printHex(byte *buffer, byte bufferSize) {

  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

/**
 * Helper routine to dump a byte array as dec values to Serial.
 */
void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(' ');
    Serial.print(buffer[i], DEC);
  }
}

String RFIDHEX(byte *buffer, byte bufferSize) {
  String value = "";
  int dataSize = sizeof(buffer);

  for (int i = 0; i < dataSize; i++) {
    char byteHex[3];                      // Almacena la representación hexadecimal de un byte
    sprintf(byteHex, "%02X ", buffer[i]);  // Convertir byte a hexadecimal
    value += byteHex;
  }

  return value;
}