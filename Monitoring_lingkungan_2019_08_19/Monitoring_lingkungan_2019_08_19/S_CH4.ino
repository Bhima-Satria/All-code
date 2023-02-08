//pull-down resistor value
int ch4_mqR = 10000;
//rO sensor value
long ch4_rO = 2626;
//min value for Rs/Ro
float ch4_minRsRo = 0.707;
//max value for Rs/Ro
float ch4_maxRsRo = 4.08;
//sensor a coefficient value
float ch4_a = 5000;
//sensor b coefficient value
float ch4_b = -1.94;

float ch4read() {
  int ch4_adcRaw = analogRead(ch4_input);
  long ch4_rS = ((1024.0 * ch4_mqR) / ch4_adcRaw) - ch4_mqR;
  //Serial.print("Rs: ");
  //Serial.println(crS);
  float ch4_rSrO = (float)ch4_rS / (float)ch4_rO;
  //Serial.print("Rs/Ro: ");
  //Serial.println(crSrO);
  float ch4_ppm = ch4_a * pow((float)ch4_rS / (float)ch4_rO, ch4_b);
  //Serial.println(cppm);
  return (ch4_ppm);
}
