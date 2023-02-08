void digit() {
  if ( tanda != 1 ) {                             // Jika Tanda tidak sama dengan 1
    angkaOne[digitOne] = value_huruf;             // Proses array dan inputan
    digitOne = digitOne + 1;                      // Proses array masuk dan penambahan array
  } else {                                        // Jika Tanda sama dengan 1
    angkaTwo[digitTwo] = value_huruf;             // Proses array dan inputan
    digitTwo = digitTwo + 1;                      // Proses array masuk dan penambahan array
  }
}
void digit1() {
  if ( tanda != 1 ) {                             // Jika Tanda tidak sama dengan 1
    angkaOne[digitOne] = value_huruf;             // Proses array dan inputan
    digitOne = digitOne;                      // Proses array masuk dan penambahan array
  } else {                                        // Jika Tanda sama dengan 1
    angkaTwo[digitTwo] = value_huruf;             // Proses array dan inputan
    digitTwo = digitTwo;                      // Proses array masuk dan penambahan array
  }
}
