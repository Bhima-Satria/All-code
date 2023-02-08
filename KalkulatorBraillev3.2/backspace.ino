void backspace() {
  if (digitTwo>0) {
    digitTwo--;
    lcd.setCursor(0, digitOne + digitTwo+2);
  }
  else{
    digitOne--;
    lcd.setCursor(0,digitOne+1);
  }
//  delay(100);
//  ku_reset(); // oke
//for (int i=0;i<10;i++){
//angkaOne[i]="";
//angkaTwo[i]="";
//angkaAwal[i]="";
//angkaAkhir[i]="";
//}
//
////  if ( tanda != 1 ) {                             // Jika Tanda tidak sama dengan 1
////    int hapusAngkaOne;
////    hapusAngkaOne = angkaOne[digitOne-1].toInt(); // Proses penghapusan data di array sebelum
////    suara(hapusAngkaOne);
////    digitOne = digitOne - 1;                      // Proses pengurangan index array sebelum
////  } else {
////    int hapusAngkaTwo;
////    hapusAngkaTwo = angkaTwo[digitTwo-1].toInt(); // Proses penghapusan data di array sesudah
////    suara(hapusAngkaTwo);
////    digitTwo = digitTwo - 1;                      // Proses pengurangan index array sesudah
////  }
}
