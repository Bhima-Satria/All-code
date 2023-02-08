#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

const int sw1 = A1;
const int sw2 = A2;
const int sw3 = A5;
const int sw4 = A3;
int ok = 0;
int next = 0;
int back = 0;
int ubah = 0;
int Y = 5000;
void setup() {

pinMode(sw1, INPUT_PULLUP);
pinMode(sw2, INPUT_PULLUP);
pinMode(sw3, INPUT_PULLUP);
pinMode(sw4, INPUT_PULLUP);
//Serial.begin(9600);
lcd.begin(16, 2);
lcd.print(" TEST TOMBOL ");
delay(2000);
lcd.clear();

}

void loop()
{

menu:
while(1)
{
lcd.clear();
lcd.setCursor(2,0);
lcd.print("Belajar Menu");
lcd.setCursor(0,1);
lcd.print("1.Goto Menu");
delay(200);

ok = digitalRead(sw1);
next = digitalRead(sw2);
back = digitalRead(sw3);
if (ok == LOW) { delay(300); goto menu1; }
if (next == LOW) { }
if (back == LOW) { }
}

menu1:
while(1)
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("1.Nasi Ayam");
lcd.setCursor(0,1);
lcd.print("2.Next 3.Back");
delay(200);

ok = digitalRead(sw1);
next = digitalRead(sw2);
back = digitalRead(sw3);
if (ok == LOW) { delay(300); goto menu2; }
if (next == LOW) { delay(300); goto menu3; }
if (back == LOW) { delay(300); goto menu; }

}
menu2:
while(1)
{

lcd.clear();
lcd.setCursor(0,0);
lcd.print("Harga=");
lcd.setCursor(6,0);
lcd.print(Y);
lcd.setCursor(0,1);
lcd.print(" 3.Back");
delay(200);

ok = digitalRead(sw1);
next = digitalRead(sw2);
back = digitalRead(sw3);
ubah = digitalRead(sw4);
if (ok == LOW) { }
if (next == LOW) { }
if (back == LOW) { delay(300); goto menu1; }
if (ubah == LOW) {  lcd.setCursor(6,0); lcd.print(Y++);}
}

menu3:
while(1)
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("1.Nasi Ikan");
lcd.setCursor(0,1);
lcd.print("2.Next 3.Back");
delay(200);

ok = digitalRead(sw1);
next = digitalRead(sw2);
back = digitalRead(sw3);
if (ok == LOW) { delay(300); goto menu4; }
if (next == LOW) { delay(300); goto menu5; }
if (back == LOW) { delay(300); goto menu1; }

}

menu4:
while(1)
{

lcd.clear();
lcd.setCursor(0,0);
lcd.print("Harga= Rp8.000");
lcd.setCursor(0,1);
lcd.print(" 3.Back");
delay(200);

ok = digitalRead(sw1);
next = digitalRead(sw2);
back = digitalRead(sw3);
if (ok == LOW) { }
if (next == LOW) { }
if (back == LOW) { delay(300); goto menu3; }

}

menu5:
while(1)
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("1.Nasi Telor");
lcd.setCursor(0,1);
lcd.print(" 3.Back");
delay(200);

ok = digitalRead(sw1);
next = digitalRead(sw2);
back = digitalRead(sw3);
if (ok == LOW) { delay(300); goto menu6; }
if (next == LOW) { }
if (back == LOW) { delay(300); goto menu3; }

}

menu6:
while(1)
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Harga= Rp7.000");
lcd.setCursor(0,1);
lcd.print(" 3.Back");
delay(200);

ok = digitalRead(sw1);
next = digitalRead(sw2);
back = digitalRead(sw3);
if (ok == LOW) { }
if (next == LOW) { }
if (back == LOW) { delay(300); goto menu5; }

}
}
