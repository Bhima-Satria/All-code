void motorAC_naik(){
  digitalWrite(motorAC1, LOW); 
  digitalWrite(motorAC2, HIGH);
}

void motorAC_turun(){
  digitalWrite(motorAC1, HIGH); 
  digitalWrite(motorAC2, LOW);
}

void motorAC_berhenti(){
  digitalWrite(motorAC1, HIGH); 
  digitalWrite(motorAC2, HIGH);
  a=1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void membuka(){
  pin_pintu(0,0);
  //lcd.setCursor(0,1);
  Serial.println("BUKA PINTU      ");
  digitalWrite(motorDC1, LOW); 
  digitalWrite(motorDC2, HIGH);
}

void terbuka(){
  //lcd.setCursor(0,1);
  Serial.println("PINTU TERBUKA   ");  
  digitalWrite(motorDC1, HIGH); 
  digitalWrite(motorDC2, HIGH); 
  tunda(3000);
}

void menutup(){
  //lcd.setCursor(0,1);
  Serial.println("TUTUP PINTU     ");  
  digitalWrite(motorDC1, HIGH); 
  digitalWrite(motorDC2, LOW);
}

void tertutup(){
  //lcd.setCursor(0,1);
  Serial.println("PINTU TERTUTUP  ");  
  digitalWrite(motorDC1, HIGH); 
  digitalWrite(motorDC2, HIGH); 
}
