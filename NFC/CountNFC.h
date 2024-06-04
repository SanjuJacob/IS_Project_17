#include <Wire.h>
#include <Adafruit_PN532.h>

#define SDA_PIN D2
#define SCL_PIN D1

// Create an instance of the PN532 sensor
Adafruit_PN532 nfc(SDA_PIN, SCL_PIN);

struct Card {
  uint8_t uid[7]; // Max UID length
  uint8_t uidLength;
};

Card cards[6]; // Array to store up to 100 different cards
int cardCount[6]; // Array to store the count for each card
int cardIndex = 0;

void setup(void) {
  Serial.begin(115200);
  Serial.println("Hello!");

  nfc.begin();
  uint32_t versiondata = nfc.getFirmwareVersion();
  if (!versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
  }

  // configure board to read RFID tags
  nfc.SAMConfig();

  Serial.println("Waiting for an NFC card ...");
}

void loop(void) {
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 }; // Buffer to store the returned UID
  uint8_t uidLength; // Length of the UID (4 or 7 bytes depending on ISO14443A card type)

  // Wait for an NFC card
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

  if (success) {
    Serial.println("Found an NFC card!");

    // Print the UID
    Serial.print("UID Length: ");Serial.print(uidLength, DEC);Serial.println(" bytes");
    Serial.print("UID Value: ");
    for (uint8_t i=0; i < uidLength; i++) {
      Serial.print(" 0x");Serial.print(uid[i], HEX);
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
        Serial.print(" 0x");Serial.print(cards[i].uid[j], HEX);
      }
      Serial.print(": "); Serial.println(cardCount[i]);
    }

    delay(1000); // Delay to avoid multiple reads of the same card
  }
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
    cardCount[i] = cardCount[i + 1];
  }
  cardIndex--;
}
