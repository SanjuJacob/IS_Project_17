int ledPin = D3;   // PWM pin for the LED
//int brightness = 128;   // LED brightness level (0-255)
int count;

void setup() {
  pinMode(ledPin, OUTPUT);// Set LED pin as output
  int count = 0; 
}

void loop() {
  if(Count>0){

       if (Count==1) {
        analogWrite(ledPin, 60);  // Set the LED brightness
        delay(1000);  // Wait for 1 second
      }
      if (Count==2) {
        analogWrite(ledPin, 128);  // Set the LED brightness
        delay(1000);  // Wait for 1 second
      }
      if (Count==3) {
        analogWrite(ledPin, 200);  // Set the LED brightness
        delay(1000);  // Wait for 1 second
      }
      if(Count==4) {
        analogWrite(ledPin, 255);  // Set the LED brightness
        delay(1000);  // Wait for 1 second
      }
  }
  else{

    analogWrite(ledPin, 0);  // Set the LED brightness
    delay(1000);
  }

