#include <Adafruit_PN532.h>

Adafruit_PN532 nfc (-1,-1);



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
  
uint8_t uid[] = {0,0,0,0,0,0,0};
uint8_t uidLength;
uint8_t success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A,uid, &uidLength);
 if (success) {
  Serial.println("Found an ISO14443A card");
  Serial.print("  UID Length:  "); Serial.print(uidLength, DEC); Serial.println (  "bytes");
  Serial.print(" UID Value: ");
  delay(30000);
 }
}
