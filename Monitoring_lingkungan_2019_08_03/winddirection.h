//sensor input PIN
int wdrInput = A9;
//max value adc
float maxVal = 4.68;
String arah;

int wdrread() {
  pinMode(wdrInput, INPUT);
  int wdr_adcRaw = analogRead(wdrInput);
  //Serial.println(wdr_adcRaw);
  float vwdr = (((float)wdr_adcRaw / 1024.0) * maxVal) + 0.15;
  //Serial.print("volt wdr= ");
  //Serial.println(vwdr);
  int wdr = (vwdr / maxVal) * 360;
  //Serial.print("Arah angin= ");
  //Serial.println(wdr);
  return (wdr);
}

//Konversi derajat ke arah mata angin
String wdrconv() {
  if ((wdrread() >= 0 && wdrread() <= 22.5) && (wdrread() >= 337.5 && wdrread() <= 360)) {
    arah = "U";
  }
  if (wdrread() > 22.5 && wdrread() <= 67.5) {
    arah = "TL";
  }
  if (wdrread() > 67.5 && wdrread() <= 112.5) {
    arah = "T";
  }
  if (wdrread() > 112.5 && wdrread() <= 157.5) {
    arah = "TG";
  }
  if (wdrread() > 157.5 && wdrread() <= 202.5) {
    arah = "S";
  }
  if (wdrread() > 202.5 && wdrread() <= 247.5) {
    arah = "BD";
  }
  if (wdrread() > 247.5 && wdrread() <= 292.5) {
    arah = "B";
  }
  if (wdrread() > 292.5 && wdrread() < 337.5) {
    arah = "BL";
  }
  //    else
  //  {
  //    arah = "-";
  //  }
  return (arah);
}

