#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h>
#include <SFEMP3Shield.h>
#include <math.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

SdFat sd;
SFEMP3Shield MP3player;
String read_Button;

// set pin numbers:
const int buttonPin1 = 3; // the number of the pushbutton pin
const int buttonPin2 = 2;
const int buttonPin3 = A0;
const int buttonPin4 = 5;
const int buttonPin5 = 6;
const int buttonPin6 = 7;
const int buttonPin_oke = 4;
const int buttonPin_backspace= A1;

// variables will change: // variable for reading the pushbutton status
int buttonState1 = 0, buttonState2 = 0, buttonState3 = 0;
int buttonState4 = 0, buttonState5 = 0, buttonState6 = 0;
int buttonState_oke = 0, buttonPin_backspace = 0; 

// variables will last change: // variable for reading the pushbutton status
int last_buttonState1 = 1, last_buttonState2 = 1;
int last_buttonState3 = 1, last_buttonState4 = 1;
int last_buttonState5 = 1, last_buttonState6 = 1;
int last_buttonState_oke = 1,,buttonPin_backspace = 1;

//variabel                                                       
int value_huruf = 0, fl_operasi = 0;          //f1_operasi = variabel operasi aritmatika

long  hasil;
int button_count = 0;
int sumbutton = 1;

int digitOne = 0;                     // Mengetahui angka yang di input pertama di lihat dr string
int digitTwo = 0;                     // Mengetahui angka yang di input pertama di lihat dr string
int tanda = 0;                        // Penanda untuk penggabungan angka pertama atau kedua
String angkaOne[10];                    // Jumlah berapa banyak inputan pertama [10]
String angkaTwo[10];                    // Jumlah berapa banyak inputan kedua [10] 

int index_a = 0;
int index_b = 0;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);
  pinMode(buttonPin5, INPUT_PULLUP);
  pinMode(buttonPin6, INPUT_PULLUP);
  pinMode(buttonPin_oke, INPUT_PULLUP);
  pinMode(buttonPin_backspace, INPUT_PULLUP);
  if (!sd.begin(SD_SEL, SPI_FULL_SPEED)) sd.initErrorHalt();
  // depending upon your SdCard environment, SPI_HAVE_SPEED may work better.
  if (!sd.chdir("/")) sd.errorHalt("sd.chdir");
  MP3player.begin();
}

void loop() {
  while(1){
    scantombol();
  }
  
  while (1)
  {
    huruf();
  }

  hasilsuara();
}
void backspace() {
  if ( tanda != 1 ) {                             // Jika Tanda tidak sama dengan 1
    int hapusAngkaOne;
    hapusAngkaOne = angkaOne[digitOne-1].toInt(); // Proses penghapusan data di array sebelum
    suara(hapusAngkaOne);
    digitOne = digitOne - 1;                      // Proses pengurangan index array sebelum
  } else {
    int hapusAngkaTwo;
    hapusAngkaTwo = angkaTwo[digitTwo-1].toInt(); // Proses penghapusan data di array sesudah
    suara(hapusAngkaTwo);
    digitTwo = digitTwo - 1;                      // Proses pengurangan index array sesudah
  }
}
void delDigit() {                                     // Fungsi digit sebelum aritmatika
  if (fl_operasi == 0){
    int delOne = angkaOne[digitOne-1].toInt();        // Proses menampilkan data yang di hapus
    Serial.print("  Hapus --> Digit ke-");            // Menampilkan ke serial monitor
    Serial.print(index_a);
    Serial.print(" =");
    Serial.println(delOne);                           // Data yang di tampilkan pada serial monitor
    index_a--;
  }
  if (fl_operasi >= 1){                               // Fungsi digit sesudah aritmatika
    int delTwo = angkaTwo[digitTwo-1].toInt();
    Serial.print("  Hapus --> Digit ke-");
    Serial.print(index_b);
    Serial.print(" =");
    Serial.println(delTwo);
    index_b--;
  }
}
void digit() {
  if ( tanda != 1 ) {                             // Jika Tanda tidak sama dengan 1
    angkaOne[digitOne] = value_huruf;             // Proses array dan inputan
    digitOne = digitOne + 1;                      // Proses array masuk dan penambahan array
  } else {                                        // Jika Tanda sama dengan 1
    angkaTwo[digitTwo] = value_huruf;             // Proses array dan inputan
    digitTwo = digitTwo + 1;                      // Proses array masuk dan penambahan array
  }
}
void hasilsuara(){
  while (1){
    switch (hasil){
      case 0:    // your hand is on the sensor
        suara(0);
        break;
      case 1:    // your hand is close to the sensor
        suara(1);
        break;
      case 2:    // your hand is a few inches from the sensor
        suara(2);
        break;
      case 3:    // your hand is nowhere near the sensor
        suara(3);
        break;
      case 4:    // your hand is on the sensor
        suara(4);
        break;
      case 5:    // your hand is close to the sensor
        suara(5);
        break;
      case 6:    // your hand is a few inches from the sensor
        suara(6);
        break;
      case 7:    // your hand is nowhere near the sensor
        suara(7);
        break;
      case 8:    // your hand is on the sensor
        suara(8);
        break;
      case 9:    // your hand is close to the sensor
        suara(9);
        break; 
    }
    delay(100);                                                                         // Delay reset otomatis 100ms = 0,1detik
    fl_operasi = 0;                                                                     // f1_operasi = variabel operasi aritmatika
    hasil = 0;
    scantombol();
  }
}
void huruf() {
  last_buttonState_oke = buttonState_oke;
  value_huruf = -1;
  if (sumbutton == 1 && button_count == 1){ //1                             Jika(nilai sumbutton sama dengan 1 dan nilai count kombinasi sama dengan 1) maka menyimpan angka 1
    suara(1);
    value_huruf = 1;
    digit();
  }
  if (sumbutton == 2 && button_count == 2){ //2                             Jika(nilai sumbutton sama dengan 2 dan nilai count kombinasi sama dengan 2) maka menyimpan angka 2
    suara(2);
    value_huruf = 2;
    digit();
  }

  if (sumbutton == 4 && button_count == 2){ //3                             Jika(nilai sumbutton sama dengan 4 dan nilai count kombinasi sama dengan 2) maka menyimpan angka 3
    suara(3);
    value_huruf = 3;
    digit();
  }

  if (sumbutton == 20 && button_count == 3){ //4                            Jika(nilai sumbutton sama dengan 20 dan nilai count kombinasi sama dengan 3) maka menyimpan angka 4
    suara(4);
    value_huruf = 4;
    digit();
  }

  if (sumbutton == 5  && button_count == 2){ //5                            Jika(nilai sumbutton sama dengan 5 dan nilai count kombinasi sama dengan 2) maka menyimpan angka 5
    suara(5);
    value_huruf = 5;
    digit();
  }

  if (sumbutton == 8 && button_count == 3){ //6                             Jika(nilai sumbutton sama dengan 8 dan nilai count kombinasi sama dengan 3) maka menyimpan angka 6
    suara(6);
    value_huruf = 6;
    digit();
  }

  if (sumbutton == 40 && button_count == 4){ //7                            Jika(nilai sumbutton sama dengan 40 dan nilai count kombinasi sama dengan 4) maka menyimpan angka 7
    suara(7);
    value_huruf = 7;
    digit();
  }

  if (sumbutton == 10 && button_count == 3){ //8                            Jika(nilai sumbutton sama dengan 10 dan nilai count kombinasi sama dengan 3) maka menyimpan angka 8
    suara(8);
    value_huruf = 8;
    digit();
  }

  if (sumbutton == 8 && button_count == 2){ //9                             Jika(nilai sumbutton sama dengan 8 dan nilai count kombinasi sama dengan 2) maka menyimpan angka 9
    suara(9);
    value_huruf = 9;
    digit();
  }

  if (sumbutton == 40 && button_count == 3){ //0                            Jika(nilai sumbutton sama dengan 40 dan nilai count kombinasi sama dengan 3) maka menyimpan angka 0
    suara(0);
    value_huruf = 0;
    digit();
  }

  if (sumbutton == 30 && button_count == 3){ // +
    fl_operasi = 1;
    suara(13);
    tanda = 1;                                                  // Jika tanda=1 maka masuk proses digit 1
  }
  if (sumbutton == 18 && button_count == 2 ){ // -
    fl_operasi = 2;
    suara(14);
    tanda = 1;
  }
  if (sumbutton == 36 && button_count == 3){ // *
    fl_operasi = 3;
    suara(15);
    tanda = 1;
  }
  if (sumbutton == 60 && button_count == 3){ // /
    fl_operasi = 4;
    suara(16);
    tanda = 1;
  }
  if (sumbutton == 90 && button_count == 3){                  // Backspace
    suara(21);                                                // Suara Di hapus
    delDigit();                                               // Pemanggilan fungsi penampilan di serial monitor
    backspace();                                              // Pemanggilan fungsi menghapus
  }
   
  if (sumbutton == 180 && button_count == 4){   // =
    tanda = 0;                                                 // Jika tanda=0 maka masuk proses digit selain 1
    
    String angkaAwal;
    for (int a = 0; a < digitOne; a = a + 1) {                 // Penggabungan digit pertama sebelum aritmatika array
      angkaAwal = angkaAwal + angkaOne[a];                     // Proses untuk mendapatkan gabungan angka
    }
    String angkaAkhir;
    for (int b = 0; b < digitTwo; b = b + 1) {                 // Setelah digit kedua setelah aritmatika array
      angkaAkhir = angkaAkhir + angkaTwo[b];                   // Proses untuk mendapatkan gabugan angka
    }
    
    Serial.print("Nilai huruf 1: ");
    Serial.println(angkaAwal);
    Serial.print("Nilai huruf 2: ");
    Serial.println(angkaAkhir);
    if (fl_operasi == 1){
      hasil = angkaAwal.toInt() + angkaAkhir.toInt();             // Proses aritmatika dari string menuju Int tambah (+)
    }
    if (fl_operasi == 2){
      hasil = angkaAwal.toInt() - angkaAkhir.toInt();             // Proses aritmatika dari string menuju Int minus (-)
    }
    if (fl_operasi == 3){
      hasil = angkaAwal.toInt() * angkaAkhir.toInt();             // Proses aritmatika dari string menuju Int perkalian (*)
    }
    if (fl_operasi == 4){
      hasil = angkaAwal.toInt() / angkaAkhir.toInt();             // Proses aritmatika dari string menuju Int bagi (/)
    }
    
    Serial.print("Hasil = ");
    Serial.println(hasil);
    digitOne = 0;
    digitTwo = 0;
    index_a = 0;
    index_b = 0;
    fl_operasi = 0;
    suara(12);
    delay(1000);
    long var;
    String hasil2;
    hasil2 = String(hasil);
    var = pow(10, ((hasil2.length()) - 1));             
    if (var >= 99) {
      var = var + 1;
    }

    while (var > 0) {                                               // Pembacaan pemecahan hasil output suara
      suara((hasil / var) % 10);
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
void scantombol() {
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);
  buttonState5 = digitalRead(buttonPin5);
  buttonState6 = digitalRead(buttonPin6);
  buttonState_oke = digitalRead(buttonPin_oke);

  if (buttonState1 != last_buttonState1) { //button 1
    if (buttonState1 == HIGH) {
      sumbutton = sumbutton * 1;                                                             // Code sejenis ini-> menghitung nilai perkalian dari kombinasi yang di masukan
      button_count++;                                                                        // Code sejenis ini-> menghitung count / berapa kali kombinasi inputan
      lcd.print("1");
      delay(100);                                                                           // Delay 100ms = 0,1detik
    }
  }
  last_buttonState1 = buttonState1;

  if (buttonState2 != last_buttonState2) { //button 2
    if (buttonState2 == HIGH) {
      sumbutton = sumbutton * 2;                                                             // Code sejenis ini-> menghitung nilai perkalian dari kombinasi yang di masukan
      button_count++;                                                                        // Code sejenis ini-> menghitung count / berapa kali kombinasi inputan
      lcd.print("2");
      delay(100);                                                                         
    }
  }
  last_buttonState2 = buttonState2;

  if (buttonState3 != last_buttonState3) { //button 3
    if (buttonState3 == HIGH) {
      sumbutton = sumbutton * 3;                                                             // Code sejenis ini-> menghitung nilai perkalian dari kombinasi yang di masukan
      button_count++;                                                                        // Code sejenis ini-> menghitung count / berapa kali kombinasi inputan
      lcd.print("3");
      delay(100);                                                                     
    }
  }
  last_buttonState3 = buttonState3;

  if (buttonState4 != last_buttonState4) { //button 4
    if (buttonState4 == HIGH) {
      sumbutton = sumbutton * 4;                                                             // Code sejenis ini-> menghitung nilai perkalian dari kombinasi yang di masukan
      button_count++;                                                                        // Code sejenis ini-> menghitung count / berapa kali kombinasi inputan
      lcd.print("4");
      delay(100);                                                                        
    }
  }
  last_buttonState4 = buttonState4;

  if (buttonState5 != last_buttonState5) { //button 5
    if (buttonState5 == HIGH) {
      sumbutton = sumbutton * 5;                                                             // Code sejenis ini-> menghitung nilai perkalian dari kombinasi yang di masukan
      button_count++;                                                                        // Code sejenis ini-> menghitung count / berapa kali kombinasi inputan
      lcd.print("5");
      delay(100);                                                                        
    }
  }
  last_buttonState5 = buttonState5;

  if (buttonState6 != last_buttonState6) { //button 6
    if (buttonState6 == HIGH) {
      sumbutton = sumbutton * 6;                                                             // Code sejenis ini-> menghitung nilai perkalian dari kombinasi yang di masukan
      button_count++;                                                                        // Code sejenis ini-> menghitung count / berapa kali kombinasi inputan
      lcd.print("6");
      delay(100);                                                                    
    }
  }
  last_buttonState6 = buttonState6;

  if (buttonState_oke != last_buttonState_oke) { //button oke
    if (buttonState_oke == HIGH) {
      lcd.print("oke");
      huruf();                                                                     
    }
  }
  last_buttonState_oke = buttonState_oke;
}
void suara(int play)//play suara
{
  MP3player.stopTrack();
  MP3player.playTrack(play);
  delay(700);                                                           // Delay 700ms = 0,7detik
  MP3player.stopTrack();
}
