#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(8, 9); // CE, CSN

byte address[] = "Node1";
char prefix [] = ";";
char prefix2[] = "+";

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}
void loop() {
  int datadebit = 90;
  String str;
  str=String(datadebit);
  char datasend[6];
  str.toCharArray(datasend,6);
  
  char kirim [32];
  strcpy(kirim, datasend);
  strcpy(kirim + strlen(datasend), prefix);
  strcpy(kirim + strlen(datasend)+strlen(prefix), address);
  strcpy(kirim + strlen(datasend)+strlen(prefix)+strlen(address), prefix2);
  radio.write(&kirim, sizeof(kirim));
  
  delay(1000);
}
