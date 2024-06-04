int servopin1 = D5; // Give the Servo Pin
int servopin2 = D3;
Servo serv1; // creating an object for 1st servo
Servo serv2;// creating an object for 2st servo
//-----------------------------------------------------------------//
int dhtpin = D4;
DHT dht22(dhtpin, DHT22); //Specify the Pin and the type
//--------------------------------------------------------------------//
Adafruit_SSD1306 display(128, 64, &Wire, -1); //SCL D1, SDA D2
//-----------------------------------------------------------------//
Adafruit_PN532 nfc (-1,-1);
struct nfcCard {
  uint8_t uid[7]; // Max UID length
  uint8_t uidLength;
};
nfcCard cards[8]; // Array to store up to 6 different cards
int cardCount[8]; // Array to store the count for each card
bool isIn[8]; 
int cardIndex = 0;
//----------------------------------------------------------------------//

int ledPin = D3;   // PWM pin for the LED  
int count;

