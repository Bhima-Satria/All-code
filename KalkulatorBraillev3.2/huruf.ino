void huruf() {
  last_buttonState_oke = buttonState_oke;
  value_huruf = -1;
  if (sumbutton == 1 && button_count == 1){ //1                             Jika(nilai sumbutton sama dengan 1 dan nilai count kombinasi sama dengan 1) maka menyimpan angka 1
    suara(1);
    value_huruf = 1;
    lcd.print("1");
    delay(100);
    digit();
  }
  if (sumbutton == 2 && button_count == 2){ //2                             Jika(nilai sumbutton sama dengan 2 dan nilai count kombinasi sama dengan 2) maka menyimpan angka 2
    suara(2);
    value_huruf = 2;
    lcd.print("2");
    delay(100);
    digit();
  }

  if (sumbutton == 4 && button_count == 2){ //3                             Jika(nilai sumbutton sama dengan 4 dan nilai count kombinasi sama dengan 2) maka menyimpan angka 3
    suara(3);
    value_huruf = 3;
    lcd.print("3");
    delay(100);
    digit();
  }

  if (sumbutton == 20 && button_count == 3){ //4                            Jika(nilai sumbutton sama dengan 20 dan nilai count kombinasi sama dengan 3) maka menyimpan angka 4
    suara(4);
    value_huruf = 4;
    lcd.print("4");
    delay(100);
    digit();
  }

  if (sumbutton == 5  && button_count == 2){ //5                            Jika(nilai sumbutton sama dengan 5 dan nilai count kombinasi sama dengan 2) maka menyimpan angka 5
    suara(5);
    value_huruf = 5;
    lcd.print("5");
    delay(100);
    digit();
  }

  if (sumbutton == 8 && button_count == 3){ //6                             Jika(nilai sumbutton sama dengan 8 dan nilai count kombinasi sama dengan 3) maka menyimpan angka 6
    suara(6);
    value_huruf = 6;
    lcd.print("6");
    delay(100);
    digit();
  }

  if (sumbutton == 40 && button_count == 4){ //7                            Jika(nilai sumbutton sama dengan 40 dan nilai count kombinasi sama dengan 4) maka menyimpan angka 7
    suara(7);
    value_huruf = 7;
    lcd.print("7");
    delay(100);
    digit();
  }

  if (sumbutton == 10 && button_count == 3){ //8                            Jika(nilai sumbutton sama dengan 10 dan nilai count kombinasi sama dengan 3) maka menyimpan angka 8
    suara(8);
    value_huruf = 8;
    lcd.print("8");
    delay(100);
    digit();
  }

  if (sumbutton == 8 && button_count == 2){ //9                             Jika(nilai sumbutton sama dengan 8 dan nilai count kombinasi sama dengan 2) maka menyimpan angka 9
    suara(9);
    value_huruf = 9;
    lcd.print("9");
    delay(100);
    digit();
  }

  if (sumbutton == 40 && button_count == 3){ //0                            Jika(nilai sumbutton sama dengan 40 dan nilai count kombinasi sama dengan 3) maka menyimpan angka 0
    suara(0);
    value_huruf = 0;
    lcd.print("0");
    delay(100);
    digit();
  }

  if (sumbutton == 12 && button_count == 2){ // +
    fl_operasi = 1;
    suara(13);
    lcd.print("+");
    delay(100);
    tanda = 1;                                                  // Jika tanda=1 maka masuk proses digit 1
  }
  if (sumbutton == 15 && button_count == 2 ){ // -
    fl_operasi = 2;
    suara(14);
    lcd.print("-");
    delay(100);
    tanda = 1;
  }
  if (sumbutton == 6 && button_count == 2){ // *
    fl_operasi = 3;
    suara(15);
    lcd.print("*");
    delay(100);
    tanda = 1;
  }
  if (sumbutton == 144 && button_count == 4){ // /
    fl_operasi = 4;
    suara(16);
    lcd.print("/");
    delay(100);
    tanda = 1;
  }
  if (sumbutton == 240 && button_count == 5) { // akar
    fl_operasi = 5;
    suara(17);
    //lcd.createChar(0, akar);
    //lcd.print(char(0));
    lcd.print("akar");
    delay(100);
    //lcd.write(byte(0));
    tanda = 1;
  }
    if (sumbutton == 20 && button_count == 2) { // pangkat
    fl_operasi = 6;
    suara(18);
    lcd.print("^");
    delay(100);
    tanda = 1;
  }
  if (sumbutton == 24 && button_count == 2){ // desimal
    //fl_operasi = 1;
    suara(18);
   //value_huruf = 00101110; // titik
    String value_koma = "."  ;  // koma
    lcd.print(".");
    //Serial.print(".");
    delay(100);
   // digit();
    digit1();
    //tanda = 0;
  }
//  if (sumbutton == 90 && button_count == 3){                  // Backspace
//    suara(21);                                                // Suara Di hapus
//    delDigit();                                               // Pemanggilan fungsi penampilan di serial monitor
//    backspace();                                              // Pemanggilan fungsi menghapus
//  }
//   
  if (sumbutton == 100 && button_count == 4){   // =
    //lcd.print("=");
    //delay(100);
   // tanda = 0;                                                 // Jika tanda=0 maka masuk proses digit selain 1
    

    for (int a = 0; a < digitOne; a = a + 1) {                 // Penggabungan digit pertama sebelum aritmatika array
      angkaAwal = angkaAwal + angkaOne[a];                     // Proses untuk mendapatkan gabungan angka
    }

    for (int b = 0; b < digitTwo; b = b + 1) {                 // Setelah digit kedua setelah aritmatika array
      angkaAkhir = angkaAkhir + angkaTwo[b];                   // Proses untuk mendapatkan gabugan angka
    }
    
    Serial.print("Nilai huruf 1: ");
    Serial.println(angkaAwal);
    Serial.print("Nilai huruf 2: ");
    Serial.println(angkaAkhir);
    if (fl_operasi == 1){
     hasil1 = (angkaAwal.toFloat() + angkaAkhir.toFloat());             // Proses aritmatika dari string menuju Int tambah (+)
        Serial.print("Hasil = ");
        lcd.print("= ");
        Serial.println(hasil1);
        lcd.setCursor(0,1);
        lcd.print(hasil1);
    }
    if (fl_operasi == 2){
      hasil1 = (double)angkaAwal.toInt() - (double)angkaAkhir.toInt();             // Proses aritmatika dari string menuju Int minus (-)
        Serial.print("Hasil = ");
        lcd.print("= ");
        Serial.println(hasil1);
        lcd.setCursor(0,1);
        lcd.print(hasil1);
    }
    if (fl_operasi == 3){
      hasil2 = angkaAwal.toInt() * angkaAkhir.toInt()  ;       // Proses aritmatika dari string menuju Int perkalian (*)
        Serial.print("Hasil = ");
        lcd.print("= ");
        Serial.println(hasil2);
        lcd.setCursor(0,1);
        lcd.print(hasil2);
    }
    if (fl_operasi == 4){
      hasil2 = (double)angkaAwal.toInt() / (double)angkaAkhir.toInt()  ;           // Proses aritmatika dari string menuju Int bagi (/)
        Serial.print("Hasil = ");
        lcd.print("= ");
        Serial.println(hasil2);
        lcd.setCursor(0,1);
        lcd.print(hasil2);
    }
    if (fl_operasi == 5){
      hasil2 = sqrt(angkaAkhir.toInt())  ;           // Proses aritmatika dari string menuju Int akar (v)
        Serial.print("Hasil = ");
        lcd.print("= ");
        Serial.println(hasil2);
        lcd.setCursor(0,1);
        lcd.print(hasil2);
    }
    //float i=0;
    if (fl_operasi == 6){
      //for (i=0;i<50;i++);
      hasil2 = pow(angkaAwal.toInt(),angkaAkhir.toInt())  ;           // Proses aritmatika dari string menuju Int pangkat (^)
        Serial.print("Hasil = ");
        lcd.print("= ");
        Serial.println(hasil2);
        lcd.setCursor(0,1);
        lcd.print(hasil2);
    
    }
//    Serial.println(hasil1);
//    lcd.println(hasil1);
//    Serial.print("Hasil = ");
//    lcd.print("= ");
    digitOne = 0;
    digitTwo = 0;
    index_a = 0;
    index_b = 0;
    fl_operasi = 0;
    suara(12);
    delay(1000);
    long var;
    String hasil3;
    hasil3 = String(hasil2);
    var = pow(10, ((hasil3.length()) - 1));             
    if (var >= 99) {
      var = var + 1;
    }

    while (var > 0) {                                               // Pembacaan pemecahan hasil output suara
      suara((hasil1 / var) % 10);
      var = var / 10;
    }
  }

  if (fl_operasi == 0 && value_huruf != -1){
    Serial.print("Digit ke-");
    Serial.print(index_a + 1);
    Serial.print(" =");
    Serial.println(value_huruf);
    index_a++;
  }
  if (fl_operasi >= 1 && value_huruf != -1){
    Serial.print("Digit ke-");
    Serial.print(index_b + 1);
    Serial.print(" =");
    Serial.println(value_huruf);
    index_b++;
  }
  sumbutton = 1;
  button_count = 0;
  scantombol();
  
}
