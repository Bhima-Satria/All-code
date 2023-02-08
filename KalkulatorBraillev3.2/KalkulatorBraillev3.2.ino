#include <string.h>
#include <SPI.h>
#include <SdFat.h>
#include <SFEMP3Shield.h>
#include <math.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <stdlib.h>
SdFat sd;
SFEMP3Shield MP3player;
String read_Button;

    String angkaAkhir; 
    String angkaAwal;
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
uint8_t akar[8] ={
  0b00000,
  0b00011,
  0b00010,
  0b00010,
  0b10010,
  0b01010,
  0b00100,
  0b00000};

// set pin numbers:
const int buttonPin1 = 3; // the number of the pushbutton pin
const int buttonPin2 = 1;
const int buttonPin3 = A0;
const int buttonPin4 = 5;
const int buttonPin5 = 6;
const int buttonPin6 = 7;
const int buttonPin_oke = 4;
const int buttonPin_del = A1;
double tegangan = A3; 

// variables will change: // variable for reading the pushbutton status
int buttonState1 = 0, buttonState2 = 0, buttonState3 = 0;
int buttonState4 = 0, buttonState5 = 0, buttonState6 = 0;
int buttonState_oke = 0, buttonState_del = 0;

// variables will last change: // variable for reading the pushbutton status
int last_buttonState1 = 1, last_buttonState2 = 1;
int last_buttonState3 = 1, last_buttonState4 = 1;
int last_buttonState5 = 1, last_buttonState6 = 1;
int last_buttonState_oke = 1, last_buttonState_del = 1;

//variabel                                                       
int value_huruf = 0, fl_operasi = 0;          //f1_operasi = variabel operasi aritmatika
String value_koma = ".";

long hasil1;
double hasil2;
int button_count = 0;
int sumbutton = 1;

int digitOne = 0;                     // Mengetahui angka yang di input pertama di lihat dr string
int digitTwo = 0;                     // Mengetahui angka yang di input pertama di lihat dr string
int tanda = 0;                        // Penanda untuk penggabungan angka pertama atau kedua
String angkaOne[10];                    // Jumlah berapa banyak inputan pertama [10]
String angkaTwo[10];                    // Jumlah berapa banyak inputan kedua [10] 

int index_a = 0;
int index_b = 0;
//void(*ku_reset)(void) = 0;

void setup() {
 // Serial.begin(115200);
  lcd.begin();
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);
  pinMode(buttonPin5, INPUT_PULLUP);
  pinMode(buttonPin6, INPUT_PULLUP);
  pinMode(buttonPin_oke, INPUT_PULLUP);
  pinMode(buttonPin_del, INPUT_PULLUP);
  pinMode(tegangan, OUTPUT);
  if (!sd.begin(SD_SEL, SPI_FULL_SPEED)) sd.initErrorHalt();
//   depending upon your SdCard environment, SPI_HAVE_SPEED may work better.
  if (!sd.chdir("/")) sd.errorHalt("sd.chdir");
  MP3player.begin();
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("Calculator");
  lcd.setCursor(5,1);
  lcd.print("Braille");
  for(int i=0;i<20;i++){
    lcd.setCursor(i,1);
    //lcd.write(255);
    delay(100);
  }
  lcd.clear();
}

void loop() {
  int komand = 17;
MP3player.stopTrack();
MP3player.playTrack(komand);
 
  while(1){
    scantombol();
  }
  
  while (1)
  {
    huruf();
  }

  hasilsuara();
  Serial.println("siap-siap reset");
  delay(100);
//  ku_reset();
}
