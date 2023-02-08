int humidity;
int lasthumidity;
int humread() {
  lasthumidity=humidity;
  humidity = dht.readHumidity();
  if (humidity == 0 )
  {
    humidity=lasthumidity;
  }
  return (humidity);
}
