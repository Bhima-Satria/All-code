// The load resistance on the board
//#define RLOAD 1.0
// Calibration resistance at atmospheric CO2 level
//#define RZERO 879.13
#include "MQ135.h"
MQ135 gasSensor = MQ135(A12);
int aval;
int asensorPin = A12;
int asensorValue = 0;

float co2read() {
  pinMode(asensorPin, INPUT);
  aval = analogRead(A12);
  //  Serial.print ("raw = ");
  //  Serial.println (val);
  float azero = gasSensor.getRZero();
  //  Serial.print ("rzero: ");
  //  Serial.println (zero);
  float co2_ppm = gasSensor.getPPM();
  //  Serial.print ("ppm: ");
  //  Serial.println (ppm);
  return (co2_ppm);
}
