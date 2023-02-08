void delDigit() {                                     // Fungsi digit sebelum aritmatika
  if (fl_operasi == 0){
    lcd.print("   ");
//    int delOne = angkaOne[digitOne-1].toInt();        // Proses menampilkan data yang di hapus
//    Serial.print("  Hapus --> Digit ke-");            // Menampilkan ke serial monitor
//    Serial.print(index_a);
    //lcd.print(index_a);
    //lcd.noDisplay(index_a);
    //lcd.clear();
//    Serial.print(" =");
//    Serial.println(delOne);                           // Data yang di tampilkan pada serial monitor
//   // lcd.clear(delOne);
//    index_a--;
  }
  if (fl_operasi >= 1){                               // Fungsi digit sesudah aritmatika
    int delTwo = angkaTwo[digitTwo-1].toInt();
    Serial.print("  Hapus --> Digit ke-");
    Serial.print(index_b);
    lcd.clear();
    Serial.print(" =");
    Serial.println(delTwo);
    //lcd.clear(delTwo);
    index_b--;
  }
}
