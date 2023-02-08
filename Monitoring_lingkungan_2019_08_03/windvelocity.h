//sensor input PIN
int wvInput = A11;
//max value adc
float maxValWv = 4.68;

int wvread() {
  pinMode(wdrInput, INPUT);
  int wv_adcRaw = analogRead(wdrInput);
  //Serial.println(wdr_adcRaw);
  float vwv = (((float)wv_adcRaw / 1024.0) * maxValWv) + 0.15;
  //Serial.print("volt wdr= ");
  //Serial.println(vwdr);
  int wv = (vwv / maxValWv) * 360;
  //Serial.print("Arah angin= ");
  //Serial.println(wdr);
  return (wv);
}


