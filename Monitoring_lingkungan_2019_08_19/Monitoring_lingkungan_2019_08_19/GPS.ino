//Fungsi Modul GPS
void gpsread()
{
  while (Serial2.available() > 0) {
    gps.encode(Serial2.read());
    if (gps.location.isUpdated()) {
      Lat = gps.location.lat();
      Lon = gps.location.lng();
      //Serial.print("Latitude= ");
      //Serial.print(Lat,8);
      //Serial.print(" Longitude= ");
      //Serial.println(Lon);
    }
  }
}
