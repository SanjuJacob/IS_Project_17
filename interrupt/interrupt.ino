int ledPin = D3;   // PWM pin for the LED
int Count = 0;
int interruptpin = D7;
volatile bool stateauto = false;

void IRAM_ATTR button_intfunc() {
  stateauto = !stateauto;
}

void setup() {
  pinMode(ledPin, OUTPUT); // Set LED pin as output
  Serial.begin(115200);
  pinMode(interruptpin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptpin), button_intfunc, FALLING); // Attach interrupt
}

void loop() {
  if (!stateauto) {
    for (Count = 0; Count <= 4; Count++) {
      if (Count > 0) {
        if (Count == 1) {
          analogWrite(ledPin, 10); // Set the LED brightness
          Serial.println("count1"); 
          delay(1000);  // Wait for 1 second
        } else if (Count == 2) {
          analogWrite(ledPin, 100);  // Set the LED brightness
          Serial.println("count2");
          delay(1000);  // Wait for 1 second
        } else if (Count == 3) {
          analogWrite(ledPin, 150);  // Set the LED brightness
          Serial.println("count3");
          delay(1000);  // Wait for 1 second
        } else if (Count == 4) {
          analogWrite(ledPin, 255);  // Set the LED brightness
          Serial.println("count4");
          delay(1000);  // Wait for 1 second
        }
      } else {
        analogWrite(ledPin, 0);  // Set the LED brightness to 0
        Serial.println("count0");
        delay(1000);
      }
    }
  } else {
    analogWrite(ledPin, 0); 
    Serial.print("insideelse");
    delay(2000);// Ensure the LED is off when in auto state
  }
}


