#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

void setup(void)
{
  Serial.begin(9600);
}

void loop()
{
  sensors_event_t event;
  mag.getEvent(&event);
  float heading = atan2(event.magnetic.y, event.magnetic.x);
  float declinationAngle = 0.22;
  heading += declinationAngle;
  if (heading < 0) {
    heading += 2 * PI;
  }
  if (heading > 2 * PI) {
    heading -= 2 * PI;
  }
  float headingDegrees = heading * 180 / M_PI;
  if (headingDegrees == 0 || headingDegrees == 360 ) {
Serial.println("N");
}
if (headingDegrees > 0 && headingDegrees < 90 ) {
Serial.print("N");
// Degree from north towards east direction
Serial.print(headingDegrees);
Serial.write(176);
Serial.println("E");
}
if (headingDegrees == 90) {
Serial.println("E");
}
if (headingDegrees > 90 && headingDegrees < 180 ) {
// Degree from south towards east direction
headingDegrees = 180 - headingDegrees;
Serial.print("S");
Serial.print(headingDegrees);
Serial.write(176);
Serial.println("E");
}
if (headingDegrees == 180) {
Serial.println("S");
}
if (headingDegrees > 180 && headingDegrees < 270 ) {
// Degree from south towards west direction
headingDegrees = headingDegrees - 180;
Serial.print("S");
Serial.print(headingDegrees);
Serial.write(176);
Serial.println("W");
}
if (headingDegrees == 270) {
Serial.println("W");
}
if (headingDegrees > 270 && headingDegrees < 360 ) {
// Degree from North towards west direction
headingDegrees = 360 - headingDegrees;
Serial.print("N");
Serial.print(headingDegrees);
Serial.write(176);
Serial.println("W");
}
delay(500);
}
