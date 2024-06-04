int ledPin = D3;   // PWM pin for the LED
//int brightness = 128;   // LED brightness level (0-255)
int count;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);// Set LED pin as output
  int count = 1; 
}

void loop() {
  count=1;
  if(count>0){

       if (count==1) {
        analogWrite(ledPin, 10);  // Set the LED brightness
        delay(1000);
        Serial.print("Test");
          // Wait for 1 second
      }
      if (count==2) {
        analogWrite(ledPin, 128);  // Set the LED brightness
        delay(1000);  // Wait for 1 second
      }
      if (count==3) {
        analogWrite(ledPin, 200);  // Set the LED brightness
        delay(1000);  // Wait for 1 second
      }
      if(count==4) {
        analogWrite(ledPin, 255);  // Set the LED brightness
        delay(1000);  // Wait for 1 second
      }
  }
  else{

    analogWrite(ledPin, 0);  // Set the LED brightness
    delay(1000);
  }
}

