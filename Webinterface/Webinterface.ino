#include <Arduino.h>
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <ESPUI.h>

int dhtpin = D2;
DHT dht22(dhtpin, DHT22);

int ledPin = D3;
volatile bool manual =false;

int currentTemperature =0;
int currenthumidity =0;

uint16_t manualops;
uint16_t tempinmain;
uint16_t huminmain;
uint16_t ledbright;
uint16_t inputtemp;
uint16_t positionMax;

const char* ssid = "Airbus";
const char* password = "Casio@123";


void sliderled( Control* sender, int value );
void SwitchChanged(Control* sender, int type);
void temperatureset(Control *sender, int value);
void humidityset(Control *sender, int type);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  dht22.begin();
  
  Serial.print("Connecting to WiFi...");
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 60) { // Retry for 30 seconds
    delay(500);
    Serial.print(".");
    attempts++;
  //default IP: 192.168.4.1
  pinMode(ledPin,OUTPUT);
  }

   if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to WiFi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  
    
   
uint16_t tabMain = ESPUI.addControl(Tab,"", "Main");
manualops = ESPUI.addControl(Switcher, "Manual Operation", "0", Emerald, tabMain, SwitchChanged);
tempinmain = ESPUI.addControl(Label, "Temperature in C", "0", Turquoise, tabMain);
huminmain = ESPUI.addControl(Label, "Humidity", "0", Alizarin, tabMain);



uint16_t tab1 = ESPUI.addControl(Tab, "", "Light Controls");

uint16_t positionMax = ESPUI.addControl(Slider, "Brightness", "0", Alizarin, tab1, sliderled);
ESPUI.addControl(Min, "", "0", None, positionMax);
ESPUI.addControl(Max, "", "255",None, positionMax);
ESPUI.updateControlValue(positionMax, "0"); // Default value (if needed)
ESPUI.updateControl(positionMax);


uint16_t tab2 = ESPUI.addControl(Tab, "", "Temperature and Humidity Controls");
uint16_t inputtemp = ESPUI.addControl(Text, "Set Temperature", "25", Emerald, tab2, temperatureset);
uint16_t inputhum = ESPUI.addControl(Text, "Set Humidity", "25", Emerald, tab2, humidityset);

ESPUI.begin("IS SOSE24 TEAM 17");

}
else { 
    Serial.println("\nFailed to connect to WiFi");
  }
}

void loop() {
  
  /*int humidity = dht22.readHumidity();
  int temperature = dht22.readTemperature();
  String valueString = String(temperature);
  String valueString1 = String(humidity);
  Serial.println("Tempval");
  Serial.println(temperature);
  ESPUI.print(tempinmain, valueString);
  ESPUI.print(huminmain, valueString1);
  delay(2000);*/

}
/*void ButtonPressed(Control* sender, int type)
{
  if(sender->id == buttonSendSerial1 && type == B_UP)
  {
    Serial.println("Button 1 pressed");
  }
  else if(sender-> id == buttonSendSerial2 && type == B_UP)
  {
    Serial.println("Button 2 pressed");
  }
}



void TextChanged(Control* sender, int type)
{
  if (sender->id == textSerial && type == T_VALUE)
  {
    Serial.print("Text from Text Input: ");
    Serial.println(sender->value);
  }
}*/

void sliderled(Control *sender, int value) {
 
  
  if(manual==true)
  {
  ESPUI.updateControlValue(positionMax, String(value));
   ESPUI.updateControl(positionMax);
  value = sender->value.toInt();
  analogWrite(ledPin, value); 
  Serial.print("LED Intensity Value ");
  Serial.println(value);
  }
  
}

void SwitchChanged (Control* sender, int type)
{
  if (sender-> id == manualops && type == S_ACTIVE)
  {
    //stateauto = false;
    manual = true;

    Serial.println("Manual Operation On");
    ESPUI.updateControlValue(positionMax, "0");
    ESPUI.updateControl(positionMax);
    Serial.println("positionMax");
    Serial.println(positionMax);
    //int value = sender->value.toInt();
    //sliderled(sender, 0);
    analogWrite(ledPin,0);
}
    //Count=0;


  else if (sender ->id == manualops && type == S_INACTIVE)
  {
    manual=false;
    Serial.println("Manual Operation Off");
    ESPUI.updateControlValue(positionMax, "0");
    ESPUI.updateControl(positionMax);
    Serial.println("positionMax");
    Serial.println(positionMax);
    analogWrite(ledPin,0);

  }
}

void temperatureset(Control *sender, int type) {
  if (manual==true)
  {

  
  if (sender->type == Text) {


    currentTemperature = sender->value.toFloat();
    String valueTempString = String(currentTemperature);

     // Set the current temperature
    Serial.print("Set temperature to: ");
    Serial.println(currentTemperature);
    ESPUI.print(tempinmain, valueTempString);
    
  }
   else if (sender->type == Label) {
    sender->value = String(currentTemperature);
    ESPUI.updateControl(sender); 
  }
  }
}
void humidityset(Control *sender, int type) {
  if (manual==true)
  {

  
  if (sender->type == Text) {


    currenthumidity = sender->value.toFloat();
    String valuehumString = String(currenthumidity);

     // Set the current temperature
    Serial.print("Set Humidity to: ");
    Serial.println(currenthumidity);
    ESPUI.print(huminmain, valuehumString);
    
  }
   else if (sender->type == Label) {
    sender->value = String(currenthumidity);
    ESPUI.updateControl(sender); 
  }
  }
}