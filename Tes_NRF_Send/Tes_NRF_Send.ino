#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";
int count = 0;

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  Serial.begin(9600); 
  Serial.println("CLEARDATA");
  Serial.println("LABEL,Date,Time,Pesan,Data Ke-");
}
void loop() {
  const char text[] = "Hello_World";
  radio.write(&text, sizeof(text));
  count++;
  
  Serial.print("DATA,DATE,TIME,"); 
  Serial.print(text);
  Serial.print(",");
  Serial.print(count);
  Serial.println(",");
  delay(1000);
}
