uint32_t suhu;
float suhu_array[15];
float tempread(){
  Wire.beginTransmission(1);
  Wire.requestFrom(1, 4);
  suhu = Wire.read();
  suhu |= Wire.read() << 8;
  suhu |= Wire.read() << 16;
  suhu |= Wire.read() << 24;
  Wire.endTransmission();
  //return((float)(suhu)/100);
  return(27);
}
