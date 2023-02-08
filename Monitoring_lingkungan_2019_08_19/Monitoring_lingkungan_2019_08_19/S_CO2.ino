int aval;
int asensorValue = 0;

float co2read() {
  aval = analogRead(co2_input);
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
