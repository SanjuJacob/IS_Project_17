int count = getCardCount();
  Serial.print("Current total count: "); // inside loop()
  Serial.println(count);
  delay(1000);

int getCardCount() {
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 }; // Buffer to store the returned UID
  uint8_t uidLength; // Length of the UID (4 or 7 bytes depending on ISO14443A card type)

  // Wait for an NFC card
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

  if (success) {
    Serial.println("Found an NFC card!");

    // Print the UID
    Serial.print("UID Length: "); Serial.print(uidLength, DEC); Serial.println(" bytes");
    Serial.print("UID Value: ");
    for (uint8_t i = 0; i < uidLength; i++) {
      Serial.print(" 0x"); Serial.print(uid[i], HEX);
    }
    Serial.println("");

    // Check if the card is already in the list
    int idx = findCard(uid, uidLength);

    if (idx == -1) {
      // New card, add to list
      addCard(uid, uidLength);
      Serial.println("New card added.");
    } else {
      // Existing card, toggle its count
      cardCount[idx]--;
      if (cardCount[idx] == 0) {
        removeCard(idx);
        Serial.println("Card removed.");
      }
    }

    // Print the current counts
    Serial.println("Current counts:");
    for (int i = 0; i < cardIndex; i++) {
      Serial.print("Card ");
      for (int j = 0; j < cards[i].uidLength; j++) {
        Serial.print(" 0x"); Serial.print(cards[i].uid[j], HEX);
      }
      Serial.print(": "); Serial.println(cardCount[i]);
    }

    delay(1000); // Delay to avoid multiple reads of the same card
  }

  // Calculate the total count
  int totalCount = 0;
  for (int i = 0; i < cardIndex; i++) {
    totalCount += cardCount[i];
  }
  
  return totalCount;
}

int findCard(uint8_t *uid, uint8_t uidLength) {
  for (int i = 0; i < cardIndex; i++) {
    if (cards[i].uidLength == uidLength && memcmp(cards[i].uid, uid, uidLength) == 0) {
      return i;
    }
  }
  return -1;
}

void addCard(uint8_t *uid, uint8_t uidLength) {
  memcpy(cards[cardIndex].uid, uid, uidLength);
  cards[cardIndex].uidLength = uidLength;
  cardCount[cardIndex] = 1;
  cardIndex++;
}

void removeCard(int index) {
  for (int i = index; i < cardIndex - 1; i++) {
    memcpy(cards[i].uid, cards[i + 1].uid, cards[i + 1].uidLength);
    cards[i].uidLength = cards[i + 1].uidLength;
    cardCount[i] = cardCount[i + 1];
  }
  cardIndex--;
}