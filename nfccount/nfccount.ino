#include <Adafruit_PN532.h>

Adafruit_PN532 nfc (-1,-1);

struct nfcCard {
  uint8_t uid[7]; // Max UID length
  uint8_t uidLength;
};

nfcCard cards[6]; // Array to store up to 6 different cards
int cardCount[6]; // Array to store the count for each card
bool isIn[6]; 
int cardIndex = 0;

void setup() {
  Serial.begin(115200);

  nfc.begin();
  if (!nfc.getFirmwareVersion())
  {
    Serial.print("Didn't find PN53x board");
    while(true)
    {
      delay(1);
    }
  }

}

void loop() {

  int Count = getCount();
  Serial.print("Inside count: ");
  Serial.println(Count);
  delay(1000);
}

int getCount() {
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
      isIn[cardIndex - 1] = true; // Mark the new card holder as inside
      Serial.println("New card added.");
    } else {
      // Existing card
      if (isIn[idx]) {
        // Card holder is inside, mark as outside
        isIn[idx] = false;
        Serial.println("Card holder left.");
      } else {
        // Card holder is outside, mark as inside
        isIn[idx] = true;
        Serial.println("Card holder entered.");
      }
    }

    // Calculate the inside count
    int insideCount = 0;
    for (int i = 0; i < cardIndex; i++) {
      if (isIn[i]) {
        insideCount++;
      }
    }

    return insideCount;
  }

  // If no NFC card is detected, return 0
  return 0;
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
    isIn[i] = isIn[i + 1];
  }
  cardIndex--;
}