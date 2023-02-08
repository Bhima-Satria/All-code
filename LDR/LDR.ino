byte ldr= A2;
float nilai=0;

void setup(){
  Serial.begin(9600);
}

void loop(){
  nilai= analogRead(ldr);
  Serial.print("Nilai ADC: ");
  Serial.println(nilai);
  delay(1000);
  float V;
  V=nilai*5/1023;
  Serial.print("Nilai V: ");
  Serial.println(V);

}
