#include <Wire.h> // memasukan library i2c
#include <Adafruit_SSD1306.h> // memasukan library LCD OLED SSD1306
#define OLED_RESET 4 
Adafruit_SSD1306 display(OLED_RESET);


void setup() { 
   display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //ganti 0x3C dengan alamat IIC LCD kalian
   display.clearDisplay(); // mengosongkan tampilan / menghapus logo adafruit
}
  
byte x;
void loop() {
  
  display.clearDisplay(); // mengosongkan tampilan
  display.setTextSize(1); // sett ukuran huruf
  display.setTextColor(WHITE); // set warna huruf
  display.setCursor(0,0); // sett posisi tampilan
  display.println("www.cronyos.com"); // mengisi karakter 

  x++;

  display.setTextSize(2); // mengosongkan tampilan
  display.setTextColor(WHITE); // set warna huruf
  display.setCursor(14,14); // sett posisi tampilan
  display.print("X : "); // mengisi karakter
  display.print(x); // mengisi karakter
  display.display(); // menampilkan karakter yang sudah disimpan

  delay(1000); // jeda 1000 miliseconds
}
