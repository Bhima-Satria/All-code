#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";
int count = 0;
unsigned long previousMillis=0;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  Serial.begin(9600);
  Serial.println("CLEARDATA");
  Serial.println("LABEL,Date,Time,Pesan,Interval");
}

void loop() {
  unsigned long currentMillis = millis();
  unsigned long interval;
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    count++;
    interval = currentMillis - previousMillis;
    Serial.print("DATA,DATE,TIME,");
    Serial.print(text);
    Serial.print(",");
    Serial.print(interval);
    Serial.println(",");
    previousMillis = currentMillis;
  }
}
