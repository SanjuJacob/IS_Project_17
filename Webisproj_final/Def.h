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
nfcCard cards[6]; // Array to store up to 6 different cards
int cardCount[6]; // Array to store the count for each card
bool isIn[6]; 
int cardIndex = 0;
//----------------------------------------------------------------------//

int ledPin = D6;   // PWM pin for the LED  

//---------------------------------------------------------------------------------------//
int interruptpin = D7;
volatile bool stateauto = false;
void IRAM_ATTR button_intfunc() {
stateauto = !stateauto;
}
//-------------------------------------------------------//

int temperature =0;
int humidity = 0;
int pos=0;
int currentCount = 0;
void Controlservotemp();

//----------------optimum value---------------------------------------------//
int optimvalue=0;


//-----------------Manual Operation Code-----------------------------------// 
int currentTemperature =0;
int optimum =0;
uint16_t manualops;
uint16_t tempinmain;
uint16_t huminmain;
uint16_t opttemp;
uint16_t ledbright;
uint16_t inputtemp;
uint16_t positionMax;

volatile bool manual = false;

const char* ssid = "eduroam";
const char* password = "Sanjac_03";

void sliderled( Control* sender, int value );
void SwitchChanged(Control* sender, int type);
void temperatureset(Control *sender, int value);
void optimumset(Control *sender, int type);
float getOptval();


//-----------------------------------------------------------//


