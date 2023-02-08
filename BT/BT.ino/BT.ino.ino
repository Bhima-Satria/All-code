#include <DMD2.h>
#include <fonts/Arial14.h>
#include <SoftwareSerial.h>
#include <SPI.h>

SoftwareSerial mySerial(2, 3); // RX, TX
byte str;

#define Panjang 1                         // Jumlah panjang Display P10
#define Lebar 1                           // Jumlah lebar Display P10

SoftDMD dmd(Panjang, Lebar); 
byte Brightness;
char BT;
int Counter = 0;
char dmdBuff[20];

void setup() {
  // Open serial communications and wait for port to open:
  dmd.setBrightness(15);
  dmd.selectFont(Arial14);
  dmd.begin();
  dmd.clearScreen();
  Serial.begin(9600);
    while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("Antrian Tiket");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Hello, world?");
}

void loop() { // run over and over
  if (mySerial.available()) {
    BT = mySerial.read();
  }
 if(BT == 'C') {
    Counter = 0;
    dmd.clearScreen();
    BT = 0;
  }
 if (BT == 'U') {
  Serial.write(mySerial.read());
    Counter++;
    BT = 0;
 }
 if (BT == 'D') {
   Serial.write(mySerial.read());
    Counter--;
    BT = 0;
  }
 sprintf(dmdBuff,"%d",Counter);
 dmd.drawString( 7, 2, dmdBuff ); 
 delay(10);
}


