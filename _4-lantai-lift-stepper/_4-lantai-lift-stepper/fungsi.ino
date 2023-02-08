void perbaruiData(){
  a=0; b=0;
  y=0, z=0;
  memori = 0;
  kunci = 0;
  /*
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);*/
}

void tunda(int d){
  //digitalWrite(diam,HIGH); 
  delay(d);
  //digitalWrite(diam,LOW); 
}

void pin_lantai(boolean a,boolean b,boolean c,boolean d){
  digitalWrite(pin_lt1, a); 
  digitalWrite(pin_lt2, b);
  digitalWrite(pin_lt3, c); 
  digitalWrite(pin_lt4, d);
}
void pin_pintu(boolean a,boolean b){
  digitalWrite(pin_up  , a); 
  digitalWrite(pin_down, b);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void turun(int kondisi,int pin){
  if ((kasus == kondisi) && (digitalRead(pin) == HIGH)) {
    motorAC_turun();
    x = 1;
  }
}

void naik(int kondisi,int pin){
  if ((kasus == kondisi) && (digitalRead(pin) == HIGH)) {
    motorAC_naik();
    x = 1;
  }
}

void berhenti(int kondisi,int pin){
  if ((kasus == kondisi) && (digitalRead(pin) == LOW)&& z == 0) {
    tunda(pengepas);
    motorAC_berhenti();
    tunda(1500);
    z = 1;
  }
  if((kasus == kondisi) && (digitalRead(pin) == LOW)&& z == 1){
    pintu();
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

