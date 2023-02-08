//max value adc
float maxValWv = 4.68;

int wvread() {
  int wv_adcRaw = analogRead(wv_input);
  //Serial.println(wdr_adcRaw);
  float vwv = (((float)wv_adcRaw / 1024.0) * maxValWv) + 0.15;
  //Serial.print("volt wdr= ");
  //Serial.println(vwdr);
  int wv = (vwv / maxValWv) * 360;
  //Serial.print("Arah angin= ");
  //Serial.println(wdr);
  return (wv);
}


