void scantombol() {
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);
  buttonState5 = digitalRead(buttonPin5);
  buttonState6 = digitalRead(buttonPin6);
  buttonState_oke = digitalRead(buttonPin_oke);
  buttonState_del = digitalRead(buttonPin_del);

  if (buttonState1 != last_buttonState1) { //button 1
    if (buttonState1 == HIGH) {
      sumbutton = sumbutton * 1;                                                             // Code sejenis ini-> menghitung nilai perkalian dari kombinasi yang di masukan
      button_count++;                                                                        // Code sejenis ini-> menghitung count / berapa kali kombinasi inputan
      delay(100);                                                                           // Delay 100ms = 0,1detik
    }
  }
  last_buttonState1 = buttonState1;

  if (buttonState2 != last_buttonState2) { //button 2
    if (buttonState2 == HIGH) {
      sumbutton = sumbutton * 2;                                                             // Code sejenis ini-> menghitung nilai perkalian dari kombinasi yang di masukan
      button_count++;                                                                        // Code sejenis ini-> menghitung count / berapa kali kombinasi inputan
      delay(100);                                                                         
    }
  }
  last_buttonState2 = buttonState2;

  if (buttonState3 != last_buttonState3) { //button 3
    if (buttonState3 == HIGH) {
      sumbutton = sumbutton * 3;                                                             // Code sejenis ini-> menghitung nilai perkalian dari kombinasi yang di masukan
      button_count++;                                                                        // Code sejenis ini-> menghitung count / berapa kali kombinasi inputan
      delay(100);                                                                     
    }
  }
  last_buttonState3 = buttonState3;

  if (buttonState4 != last_buttonState4) { //button 4
    if (buttonState4 == HIGH) {
      sumbutton = sumbutton * 4;                                                             // Code sejenis ini-> menghitung nilai perkalian dari kombinasi yang di masukan
      button_count++;                                                                        // Code sejenis ini-> menghitung count / berapa kali kombinasi inputan
      delay(100);                                                                        
    }
  }
  last_buttonState4 = buttonState4;

  if (buttonState5 != last_buttonState5) { //button 5
    if (buttonState5 == HIGH) {
      sumbutton = sumbutton * 5;                                                             // Code sejenis ini-> menghitung nilai perkalian dari kombinasi yang di masukan
      button_count++;                                                                        // Code sejenis ini-> menghitung count / berapa kali kombinasi inputan
      delay(100);                                                                        
    }
  }
  last_buttonState5 = buttonState5;

  if (buttonState6 != last_buttonState6) { //button 6
    if (buttonState6 == HIGH) {
      sumbutton = sumbutton * 6;                                                             // Code sejenis ini-> menghitung nilai perkalian dari kombinasi yang di masukan
      button_count++;                                                                        // Code sejenis ini-> menghitung count / berapa kali kombinasi inputan
      delay(100);                                                                    
    }
  }
  last_buttonState6 = buttonState6;

  if (buttonState_del != last_buttonState_del) { //button del
    if (buttonState_del == HIGH){
      suara(21);
      delDigit();
      backspace();
      lcd.clear();
    }
  }
  last_buttonState_del = buttonState_del;

  if (buttonState_oke != last_buttonState_oke) { //button oke
    if (buttonState_oke == HIGH) {
      huruf();                                                                     
    }
  }
  last_buttonState_oke = buttonState_oke;
}
