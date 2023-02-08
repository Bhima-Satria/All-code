//sensor input PIN
int ch4_mqInput = A13;
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

void setup() {
  // put your setup code here, to run once:
    pinMode(ch4_mqInput, INPUT);
    Serial.begin(9600);

}

void loop() {
  int ch4_adcRaw = analogRead(ch4_mqInput);
  float V = ch4_adcRaw*5.00/1024;
  long ch4_rS = ((1024.0 * ch4_mqR) / ch4_adcRaw) - ch4_mqR;
  Serial.print("Volt: ");
  Serial.println(V);
  float ch4_rSrO = (float)ch4_rS / (float)ch4_rO;
  //Serial.print("Rs/Ro: ");
  //Serial.println(crSrO);
  float ch4_ppm = ch4_a * pow((float)ch4_rS / (float)ch4_rO, ch4_b);
  Serial.print("ch4_ppm: ");
  Serial.println(ch4_ppm);
//  return (ch4_ppm);
  Serial.print("ADC :");
  Serial.println(ch4_adcRaw);
  delay(3000);
}
