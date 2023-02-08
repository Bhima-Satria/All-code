#include "MQ135.h"
MQ135 gasSensor = MQ135(A12);
int aval;
int asensorPin = A12;
int asensorValue = 0;

void setup() {
   pinMode(asensorPin, INPUT);
   Serial.begin(9600);
}

void loop() {
 aval = analogRead(A12);
    Serial.print ("ADC = ");
    Serial.println (aval);
  float V = aval*5.00/1024;
    Serial.print ("Volt: ");
    Serial.println (V);
  float co2_ppm = gasSensor.getPPM();
    Serial.print ("ppm: ");
    Serial.println (co2_ppm);
  delay(3000);
}
