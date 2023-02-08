void pintu(){
  if(a == 1){
    membuka();
  } 
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  if((digitalRead(lmBuka) == LOW) && (digitalRead(lmTutup) == HIGH) && b == 0){ //pintu terbuka selama 5 detik
    a=0; 
    y = 0;
    terbuka();
    b=1;
    Serial.println(b);
  } 
  if((digitalRead(lmBuka) == LOW) && (digitalRead(lmTutup) == HIGH) && b == 1){ //pintu menutup
    y=1;
    menutup();
    b=2;
    Serial.println(b);
  }
  if((digitalRead(lmBuka) == HIGH) && (digitalRead(lmTutup) == LOW) && b == 2){ // pintu tertutup 
    y = 0;
    tertutup();
    x = 0;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if(((digitalRead(buka) == LOW)||(digitalRead(sensor) == HIGH)) && y == 1 && a==0){
    membuka();
    b=0;
  }
  if((digitalRead(tutup) == LOW) && y == 1 && a==0){
    menutup();
    b=2;
  }
}
