//Aktivasi  reset
void resetFunc()
{
  digitalWrite(relay2, HIGH);
}

//Fungsi automatic reset
void rstactive() {
  if (Voltage <= 7.5)
  {
    resetcond = 1;
  }
  if ((resetcond == 1) && (Voltage >= 7.7))
  {
    resetFunc();
  }
}
