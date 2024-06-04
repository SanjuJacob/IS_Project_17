//Include the header files
#include "Lib.h"
#include "Def.h"



void setup(){

  Serial.begin(115200);
  //------------------------------------------------//
  dht22.begin(); //dht begin code
  //-----------------------------------------------//
  serv1.attach(servopin1); //allocate first servo
  serv2.attach(servopin2); //allocate second servo
  serv1.write(90); //initialize servo to 90 degree which is off
  serv2.write(90);
  //-------------------------------------------------//
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0X3C))
  {
    Serial.println("SSD1306 Allocate failed");
    while(true);
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
  //display.setCursor(0,0);
  //display.println("Hello World");
  //display.display();
  //-------------------------------------------------//
   nfc.begin();
  if (!nfc.getFirmwareVersion())
  {
    Serial.print("Didn't find PN53x board"); // when the board is not found.
    while(true)
    {
      delay(1);
    }
  }
//-------------------------------------------------------//
pinMode(ledPin, OUTPUT);// Set LED pin as output
  int Count = 0;

}

void loop()

{

  float temp = dht22.readTemperature(); //Read the temperature
  float hum = dht22.readHumidity(); // Read the humidity
//--------------------------------------------------------------------------------//
  display.print("Temp in C: "); // Code for printing Temp AND Hum in OLED
  display.println(temp);
  display.display();
  display.print("Humidity: ");
  display.println(hum);
  display.display();
  delay(1000);
  display.clearDisplay();
  display.setCursor(0,28);
//---------------------------------------------------------------------------------//
  Serial.print("Temperature in C: ");
  Serial.print(temp);
  Serial.print(" C");
  Serial.println();
  Serial.print(" Humidity: ");
  Serial.println(hum);
  Serial.println();
  delay(2000); //Measure temp and hum in Serial monitor
 //--------------------------------------------------------------------------------// 
 int Count = getCount();
  Serial.print("Count: "); // get the count value from the functions.
  Serial.println(Count);
  delay(1000);
//-----------------------------------------------------------------------------//

if(Count>0){

       if (Count==1 || Count==2 ) {
        analogWrite(ledPin, 60);  // Set the LED brightness
        delay(1000);  // Wait for 1 second
      }
      if (Count==3 || Count==4) {
        analogWrite(ledPin, 128);  // Set the LED brightness
        delay(1000);  // Wait for 1 second
      }
      if (Count==5 || Count ==6 ) {
        analogWrite(ledPin, 200);  // Set the LED brightness
        delay(1000);  // Wait for 1 second
      }
      if(Count == 7 || Count == 8) {
        analogWrite(ledPin, 255);  // Set the LED brightness
        delay(1000);  // Wait for 1 second
      }
  }
  else{

    analogWrite(ledPin, 0);  // Set the LED brightness
    delay(1000);
  }
  //---------------------------------------------------------------------------//
  int pos;
  // Temperature between 45 C to 125 C
  if ((int(temp)>= 45) && (int(temp)<=125))
  {
    
      Serial.println("Temp range in C: 45-125 ");
      for (pos=0;pos<=180;pos+=1)
      {
        serv1.write(pos);
        delay(5);
      }
      for (pos=180;pos>=0;pos-=1)
      {
        serv1.write(pos);
        delay(5);
      }
  }
// Temperature between 28 C to 44 C
  if ((int(temp)>= 28) && (int(temp) <= 44))
  {
      
    Serial.println("Temp range in C: 28 - 44 ");
      for (pos=0;pos<=180;pos+=1)
      {
        serv1.write(pos);
        delay(25);
      }
      for (pos=180;pos>=0;pos-=1)
      {
        serv1.write(pos);
        delay(25);
      }
  }

// Temperature between 24 C to 27 C (Switch off cooler)
  if ((int(temp)>= 24) && (int(temp) <= 27))
  {
    Serial.println("Temp range in C : 24-27 ");
    serv1.write(90); //To turn off
    
    
  }

// Temperature between 10 C to  23C (Turn on Heater)

  if ((int(temp)>= 10) && (int(temp) <= 23))
  {
      Serial.println("Temp range in C : 10-23 ");
      for (pos=0;pos<=360;pos+=1)
      {
        serv2.write(pos);
        delay(50);
      }
      for (pos=180;pos>=0;pos-=1)
      {
        serv2.write(pos);
        delay(50);
      }
  }
  // Temperature between -10 C to  9 C (Turn on Heater)
   if ((int(temp)>= -10) && (int(temp) <= 9))
  {
      Serial.println("Temp range in C : -10-9 ");
      for (pos=0;pos<=360;pos+=1)
      {
        serv2.write(pos);
        delay(25);
      }
      for (pos=180;pos>=0;pos-=1)
      {
        serv2.write(pos);
        delay(25);
      }
  }
  // Temperature between -40 C to  -11 C (Turn on Heater)
   if ((int(temp)>= -40) && (int(temp) <= -11))
  {
      Serial.println("Temp range in C : -40-(-11) ");
      for (pos=0;pos<=360;pos+=1)
      {
        serv2.write(pos);
        delay(5);
      }
      for (pos=180;pos>=0;pos-=1)
      {
        serv2.write(pos);
        delay(5);
      }
  }
//-----------------------------------------------------------------------------//

}

//---------------------------------------------------------------------------//
//other functions for nfc card count.

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
      isIn[cardIndex - 1] = true; // Mark the new card holder as in
      Serial.println("New card added.");
    } else {
      // Existing card
      if (isIn[idx]) {
        // Card holder is in, mark as out
        isIn[idx] = false;
        Serial.println("Card holder left.");
      } else {
        // Card holder is out, mark as in
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
//------------------------------------------------------------------------------------------------------//
