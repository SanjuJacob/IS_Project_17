#include <ESP8266WiFi.h>
#include<Servo.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

int servopin1 = D5;
Servo serv1;

void setup() {
  // put your setup code here, to run once:
  serv1.attach(servopin1);
}

void loop() {
  // put your main code here, to run repeatedly:
    int pos;
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
