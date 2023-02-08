#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "Regu1";
String cmd;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}
void loop() {
  
  if (radio.available()) {
    char text[64] = "";
    radio.read(&text, sizeof(text));
    Serial.print("Terima data : ");
    Serial.println(text);
    cmd+=text;
    Serial.print("Latitude : "); Serial.println(cmd.substring(0,9));
    Serial.print("Longitude: "); Serial.println(cmd.substring(10,20));
    Serial.print("Dari regu: "); Serial.println(cmd.substring(21,26));
    cmd="";
  }
}
