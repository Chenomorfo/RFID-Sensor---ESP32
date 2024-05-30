bool IsNewCard(byte *nId, byte *pId) {
  if (pId[0] != nId[0] || pId[1] != nId[1] || pId[2] != nId[2] || pId[3] != nId[3])
    return true;
  return false;
}

void EntryPass() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(50);
  digitalWrite(BUZZER_PIN, LOW);
  }

void SuccessPass() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(50);
  digitalWrite(BUZZER_PIN, LOW);
  delay(50); 
  digitalWrite(BUZZER_PIN, HIGH);
  delay(50); 
  digitalWrite(BUZZER_PIN, LOW);
  delay(50); 
  digitalWrite(BUZZER_PIN, HIGH);
  delay(50); 
  digitalWrite(BUZZER_PIN, LOW);
}

void UnsuccessPass() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(600);
  digitalWrite(BUZZER_PIN, LOW);
  delay(250); 
  digitalWrite(BUZZER_PIN, HIGH);
  delay(600); 
  digitalWrite(BUZZER_PIN, LOW);
}