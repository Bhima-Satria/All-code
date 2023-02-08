#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "DHT.h"

RF24 radio(9, 10); // CE, CSN
#define DHTPIN 4
#define DHTTYPE DHT11
#define SensorPin A0
#define ONE_WIRE_BUS 6 //Pin Sensor Suhu DS18B20

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float suhu;
float kelembaban;
int Soil;
float humi;
String data1;
int count=0;

DHT dht(DHTPIN, DHTTYPE);

const byte address[6] = "00001";

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  Serial.begin(9600);
  dht.begin();
  sensors.begin();
}
void loop() {
  sensors.requestTemperatures();
  //  suhu = sensors.getTempCByIndex(0);
  suhu = dht.readTemperature();
  humi = dht.readHumidity() - 9;
  kelembaban = analogRead(SensorPin);
  kelembaban = map(kelembaban, 880, 300, 0, 100);
  Soil = kelembaban;

  if (Soil < 0) {
    Soil = 0;
  }
  else if (Soil > 100) {
    Soil = 100;
  } else Soil = kelembaban;

  count++;

  data1 = "Data ke-" + String(count) + "S" + String(suhu) + "T" + String(Soil) + "U" + String(humi) + "," + "Node2";
  char data_send [data1.length() + 1];
  data1.toCharArray(data_send, data1.length() + 1);

  const char text[data1.length() + 1];
  strcpy(text, data_send);

  radio.write(&text, sizeof(text));
  delay(600000);
}
