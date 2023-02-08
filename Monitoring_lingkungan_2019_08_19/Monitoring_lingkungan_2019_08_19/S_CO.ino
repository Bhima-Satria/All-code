//sensor input PIN
int co_mqInput = A15;
//pull-down resistor value
int co_mqR = 100;
//rO sensor value
long co_rO = 93;
//min value for Rs/Ro
float co_minRsRo = 0.089;
//max value for Rs/Ro
float co_maxRsRo = 1;
//sensor a coefficient value
float co_a = 100;
//sensor b coefficient value
float co_b = -1.52;

float coread() {
  int co_adcRaw = analogRead(co_input);
  long co_rS = ((1024.0 * co_mqR) / co_adcRaw) - co_mqR;
  //Serial.print("Rs: ");
  //Serial.println(rS);
  float co_rSrO = (float)co_rS / (float)co_rO;
  //Serial.print("Rs/Ro: ");
  //Serial.println(rSrO);
  float co_ppm = co_a * pow((float)co_rS / (float)co_rO, co_b);
  //float vol = ppm / 10000;
  return (co_ppm);
}
